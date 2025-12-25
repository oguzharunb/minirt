/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:49:11 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 13:18:20 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "camera.h"
# include "ray.h"
# include "vector.h"

typedef enum e_hit_type
{
	HIT_NONE = 0,
	HIT_SPHERE,
	HIT_PLANE,
	HIT_CYLINDER
}						t_hit_type;

typedef struct s_hit
{
	t_hit_type			type;
	void				*obj;
	double				t;
}						t_hit;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct s_sphere
{
	t_vec3				center;
	double				radius;
	t_rgb				color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				point;
	t_vec3				normal;
	t_rgb				color;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				axis;
	double				radius;
	double				height;
	t_rgb				color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_ambient
{
	double				ratio;
	t_rgb				color;
}						t_ambient;

typedef struct s_light
{
	t_vec3				position;
	double				ratio;
	t_rgb				color;
}						t_light;

typedef struct s_scene
{
	int					render_width;
	int					render_height;
	int					scale;
	double				aspect_ratio;
	t_camera			camera;
	t_ambient			amb;
	t_light				light;
	t_sphere			*spheres;
	t_plane				*planes;
	t_cylinder			*cylinders;
}						t_scene;

int						hit_cylinder(t_cylinder *cy, t_ray *ray, double *t);
int						hit_sphere(t_sphere *s, t_ray *ray, double *t);
int						hit_plane(t_plane *pl, t_ray *ray, double *t);

void					free_spheres(t_sphere *sp);
void					free_planes(t_plane *pl);
void					free_cylinders(t_cylinder *cy);

t_vec3					sphere_normal(t_sphere *sp, t_vec3 p);

t_vec3					plane_normal(t_plane *pl);

t_vec3					cylinder_normal(t_cylinder *cy, t_vec3 p);

#endif
