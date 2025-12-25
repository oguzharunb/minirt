/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:06:32 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 15:37:15 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// ARTIK BUNLAR SABİT PENCERE BOYUTUMUZ (1600x900)
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define SCALE 10
# define SCREEN_WIDTH 320
# define SCREEN_HEIGHT 180

# ifdef __linux__
#  include <X11/keysym.h>
#  define KEY_ESC XK_Escape
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_R XK_r
#  define KEY_SPACE XK_space
#  define KEY_SHIFT XK_Shift_L
#  define KEY_LEFT XK_Right
#  define KEY_RIGHT XK_Left
#  define KEY_UP XK_Down
#  define KEY_DOWN XK_Up
# endif

# define MOVE_STEP 0.35
# define ROT_STEP 0.0523598 // ~3 derece radyan

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
void		render(t_data *img, t_scene *scene);
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

#endif
