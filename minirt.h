/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:49:11 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 17:02:45 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define SCALE 10
# define SCREEN_WIDTH 320
# define SCREEN_HEIGHT 180

# ifdef __linux__
#  define KEY_ESC 0xff1b
#  define KEY_W 0x0077
#  define KEY_A 0x0061
#  define KEY_S 0x0073
#  define KEY_D 0x0064
#  define KEY_R 0x0072
#  define KEY_SPACE 0x0020
#  define KEY_SHIFT 0xffe1
#  define KEY_LEFT 0xff53
#  define KEY_RIGHT 0xff51
#  define KEY_UP 0xff54
#  define KEY_DOWN 0xff52
# endif

# define MOVE_STEP 0.35
# define ROT_STEP 0.0523598

# include "camera.h"
# include "objects.h"
# define EPS 1e-4

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_scene	scene;
}			t_app;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		render(t_app *app);
void		redraw(t_app *app);

void		free_scene(t_scene *scene);
int			on_close(void *param);

int			on_key(int key, void *param);

int			scene_closest_hit(t_scene *scene, t_ray *ray, t_hit *hit);

t_vec3		get_normal(t_hit *hit, t_vec3 p);
void		orient_normal(t_vec3 *n, t_ray *ray);

int			rgb_to_int(t_rgb c);
int			get_obj_color(t_hit *hit);
int			is_in_shadow_scene(t_scene *scene, t_vec3 p, t_vec3 n,
				t_vec3 l_pos);

void		switch_to_low_res(t_scene *scene);
void		switch_to_high_res(t_scene *scene);
#endif