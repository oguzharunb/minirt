#include "minirt.h"
#include "objects.h"
#include "ray.h"
#include "mlx_utils.h"
#include "vector.h"
#include "lighting_utils.h" // lambert_shade kullanıyorsan
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-4

typedef enum e_hit_type
{
	HIT_NONE = 0,
	HIT_SPHERE,
	HIT_PLANE,
	HIT_CYLINDER
}	t_hit_type;

typedef struct s_hit
{
	t_hit_type	type;
	void		*obj;
	double		t;
}	t_hit;

static int	clamp255(int v)
{
	if (v < 0) return 0;
	if (v > 255) return 255;
	return v;
}

static int	rgb_to_int(t_rgb c)
{
	int r = clamp255(c.r);
	int g = clamp255(c.g);
	int b = clamp255(c.b);
	return ((r << 16) | (g << 8) | b);
}

static t_vec3	sphere_normal_local(t_sphere *sp, t_vec3 p)
{
	return (vec_normalize(vec_sub(p, sp->center)));
}

static t_vec3	plane_normal_local(t_plane *pl)
{
	return (vec_normalize(pl->normal));
}

static t_vec3	cylinder_normal_local(t_cylinder *cy, t_vec3 p)
{
	t_vec3	v = vec_sub(p, cy->center);
	double	proj = vec_dot(v, cy->axis);
	t_vec3	radial = vec_sub(v, vec_mul(cy->axis, proj));

	if (cy->height > 0.0)
	{
		double half = cy->height * 0.5;
		if (fabs(proj - half) < 1e-3)
			return (cy->axis);
		if (fabs(proj + half) < 1e-3)
			return (vec_mul(cy->axis, -1.0));
	}
	return (vec_normalize(radial));
}

static void	orient_normal_against_ray(t_vec3 *n, t_ray *ray)
{
	// normal ray yönüyle aynı yöne bakıyorsa ters çevir
	if (vec_dot(*n, ray->direction) > 0.0)
		*n = vec_mul(*n, -1.0);
}

static int	scene_closest_hit(t_scene *scene, t_ray *ray, t_hit *hit)
{
	double		t;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	hit->type = HIT_NONE;
	hit->obj = NULL;
	hit->t = 1e30;

	sp = scene->spheres;
	while (sp)
	{
		if (hit_sphere(sp, ray, &t) && t > EPS && t < hit->t)
		{
			hit->t = t;
			hit->type = HIT_SPHERE;
			hit->obj = sp;
		}
		sp = sp->next;
	}

	pl = scene->planes;
	while (pl)
	{
		if (hit_plane(pl, ray, &t) && t > EPS && t < hit->t)
		{
			hit->t = t;
			hit->type = HIT_PLANE;
			hit->obj = pl;
		}
		pl = pl->next;
	}

	cy = scene->cylinders;
	while (cy)
	{
		if (hit_cylinder(cy, ray, &t) && t > EPS && t < hit->t)
		{
			hit->t = t;
			hit->type = HIT_CYLINDER;
			hit->obj = cy;
		}
		cy = cy->next;
	}

	return (hit->type != HIT_NONE);
}

static int	is_in_shadow_scene(t_scene *scene, t_vec3 p, t_vec3 n, t_vec3 light_pos)
{
	t_ray		shadow_ray;
	t_hit		hit;
	t_vec3		to_light;
	double		dist;

	to_light = vec_sub(light_pos, p);
	dist = vec_length(to_light);
	if (dist <= EPS)
		return (0);

	shadow_ray.origin = vec_add(p, vec_mul(n, EPS));
	shadow_ray.direction = vec_mul(to_light, 1.0 / dist);

	if (!scene_closest_hit(scene, &shadow_ray, &hit))
		return (0);

	// Işığa varmadan önce bir şey kesiyorsa gölge
	if (hit.t > EPS && hit.t < dist - EPS)
		return (1);
	return (0);
}
static void	put_block(t_data *img, int sx, int sy, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < SCALE)
	{
		dx = 0;
		while (dx < SCALE)
		{
			my_mlx_pixel_put(img, sx + dx, sy + dy, color);
			dx++;
		}
		dy++;
	}
}

static int	shade_pixel(t_scene *scene, t_ray *ray)
{
	t_hit	hit;
	t_vec3	p;
	t_vec3	n;
	int		col_int;
	int		shadow;

	if (!scene_closest_hit(scene, ray, &hit))
		return (0x87CEEB);

	p = ray_at(ray, hit.t);

	if (hit.type == HIT_SPHERE)
	{
		t_sphere *sp = (t_sphere *)hit.obj;
		n = sphere_normal_local(sp, p);
		col_int = rgb_to_int(sp->color);
	}
	else if (hit.type == HIT_PLANE)
	{
		t_plane *pl = (t_plane *)hit.obj;
		n = plane_normal_local(pl);
		col_int = rgb_to_int(pl->color);
	}
	else
	{
		t_cylinder *cy = (t_cylinder *)hit.obj;
		n = cylinder_normal_local(cy, p);
		col_int = rgb_to_int(cy->color);
	}

	orient_normal_against_ray(&n, ray);
	shadow = is_in_shadow_scene(scene, p, n, scene->light.position);

	return (lambert_shade(
		col_int,
		p,
		n,
		scene->light.position,
		scene->amb.ratio,
		shadow ? 0.0 : scene->light.ratio
	));
}

void	render(t_data *img, t_scene *scene)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;

	const int rw = scene->render_width;
	const int rh = scene->render_height;

	y = 0;
	while (y < rh)
	{
		x = 0;
		while (x < rw)
		{
			set_ray(&ray, &scene->camera, x, y /*, rw, rh */);
			color = shade_pixel(scene, &ray);
			put_block(img, x * SCALE, y * SCALE, color);
			x++;
		}
		y++;
	}
}