/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:19:27 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 15:36:18 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting_utils.h"
#include "minirt.h"
#include "mlx_utils.h"
#include "objects.h"
#include "ray.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

static void put_block(t_data *img, int sx, int sy, int color, int scale)
{
	int dx;
	int dy;

	dy = 0;
	while (dy < scale)
	{
		dx = 0;
		while (dx < scale)
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
	int		col;
	t_shade	s;

	if (!scene_closest_hit(scene, ray, &hit))
		return (0x87CEEB);
	p = ray_at(ray, hit.t);
	n = get_normal(&hit, p);
	col = get_obj_color(&hit);
	orient_normal(&n, ray);
	s.p = p;
	s.n = n;
	s.light_pos = scene->light.position;
	s.ambient = scene->amb.ratio;
	s.intensity = scene->light.ratio;
	if (is_in_shadow_scene(scene, p, n, scene->light.position))
		s.intensity = 0.0;
	return (lambert_shade(col, s));
}

void render(t_app *app)
{
	int     x;
	int     y;
	int     color;
	t_ray   ray;
	t_scene *scene;
	t_data  *img;

	scene = &app->scene;
	img = &app->img;
	y = 0;
	while (y < scene->render_height)
	{
		x = 0;
		while (x < scene->render_width)
		{
			set_ray(&ray, &scene->camera, x, y, scene->render_width, scene->render_height);
			color = shade_pixel(scene, &ray);
			put_block(img, x * scene->scale, y * scene->scale, color, scene->scale);
			x++;
		}
		mlx_put_image_to_window(app->mlx, app->win, img->img, 0, 0);
		y++;
	}
}