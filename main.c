#include "minirt.h"
#include "mlx.h"
#include "objects.h"
#include "parser.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifdef __linux__
#include <X11/keysym.h>
#define KEY_ESC XK_Escape
#define KEY_W XK_w
#define KEY_A XK_a
#define KEY_S XK_s
#define KEY_D XK_d
#define KEY_LEFT XK_Right
#define KEY_RIGHT XK_Left
#define KEY_UP XK_Down
#define KEY_DOWN XK_Up
#else
// macOS keycodes (MiniLibX)
# define KEY_ESC    53

# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2

# define KEY_LEFT   123
# define KEY_RIGHT  124
# define KEY_DOWN   125
# define KEY_UP     126
#endif

#define MOVE_STEP 0.35
#define ROT_STEP (3.0 * M_PI / 180.0)

typedef struct s_app
{
	void *mlx;
	void *win;
	t_data img;
	t_scene scene;
} t_app;

static t_vec3 rotate_around_axis(t_vec3 v, t_vec3 axis, double ang)
{
	double c = cos(ang);
	double s = sin(ang);

	axis = vec_normalize(axis);
	return vec_add(
		vec_add(
			vec_mul(v, c),
			vec_mul(vec_cross(axis, v), s)),
		vec_mul(axis, vec_dot(axis, v) * (1.0 - c)));
}

static void camera_rebuild(t_camera *cam)
{
	t_vec3 global_up;

	cam->forward = vec_normalize(cam->forward);

	global_up = vec(0, 1, 0);
	if (fabs(cam->forward.y) > 0.999)
		cam->right = vec_normalize(vec_cross(vec(0, 0, 1), cam->forward));
	else
		cam->right = vec_normalize(vec_cross(global_up, cam->forward));

	cam->up = vec_cross(cam->forward, cam->right);

	cam->horizontal = vec_mul(cam->right, cam->viewport_w);
	cam->vertical = vec_mul(cam->up, cam->viewport_h);

	cam->lower_left = vec_sub(cam->origin, vec_mul(cam->horizontal, 0.5));
	cam->lower_left = vec_sub(cam->lower_left, vec_mul(cam->vertical, 0.5));
	cam->lower_left = vec_add(cam->lower_left, cam->forward);
}

static void redraw(t_app *app)
{
	render(&app->img, &app->scene);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
}

// static int on_close(void *param)
// {
// 	(void)param;
// 	exit(0);
// 	return (0);
// }

void free_scene(t_scene *scene)
{
	t_sphere *sp;
	t_sphere *sp_next;
	t_plane *pl;
	t_plane *pl_next;
	t_cylinder *cy;
	t_cylinder *cy_next;

	sp = scene->spheres;
	while (sp)
	{
		sp_next = sp->next;
		free(sp);
		sp = sp_next;
	}
	scene->spheres = NULL;
	pl = scene->planes;
	while (pl)
	{
		pl_next = pl->next;
		free(pl);
		pl = pl_next;
	}
	scene->planes = NULL;
	cy = scene->cylinders;
	while (cy)
	{
		cy_next = cy->next;
		free(cy);
		cy = cy_next;
	}
	scene->cylinders = NULL;
}

static int on_close(void *param)
{
	t_app *app = (t_app *)param;
	void *mlx_ptr = app->mlx;
	if (app->img.img)
		mlx_destroy_image(app->mlx, app->img.img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	free_scene(&app->scene);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);

	exit(0);
	return (0);
}


static int on_key(int key, void *param)
{
	t_app *app = (t_app *)param;
	t_camera *cam = &app->scene.camera;
	int changed = 0;

	if (key == KEY_ESC)
	{
		on_close(param);
		return (0);
	}
	if (key == KEY_W)
	{
		cam->origin = vec_add(cam->origin, vec_mul(cam->forward, MOVE_STEP));
		changed = 1;
	}
	if (key == KEY_S)
	{
		cam->origin = vec_sub(cam->origin, vec_mul(cam->forward, MOVE_STEP));
		changed = 1;
	}
	if (key == KEY_D)
	{
		cam->origin = vec_add(cam->origin, vec_mul(cam->right, MOVE_STEP));
		changed = 1;
	}
	if (key == KEY_A)
	{
		cam->origin = vec_sub(cam->origin, vec_mul(cam->right, MOVE_STEP));
		changed = 1;
	}
	if (key == KEY_LEFT)
	{
		cam->forward = rotate_around_axis(cam->forward, vec(0, 1, 0), +ROT_STEP);
		changed = 1;
	}
	if (key == KEY_RIGHT)
	{
		cam->forward = rotate_around_axis(cam->forward, vec(0, 1, 0), -ROT_STEP);
		changed = 1;
	}
	if (key == KEY_UP)
	{
		t_vec3 new_f = rotate_around_axis(cam->forward, cam->right, +ROT_STEP);
		if (fabs(vec_dot(vec_normalize(new_f), vec(0, 1, 0))) < 0.999)
		{
			cam->forward = new_f;
			changed = 1;
		}
	}
	if (key == KEY_DOWN)
	{
		t_vec3 new_f = rotate_around_axis(cam->forward, cam->right, -ROT_STEP);
		if (fabs(vec_dot(vec_normalize(new_f), vec(0, 1, 0))) < 0.999)
		{
			cam->forward = new_f;
			changed = 1;
		}
	}

	if (changed)
	{
		camera_rebuild(cam);
		redraw(app);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_app app;

	if (ac != 2)
	{
		printf("using: ./minirt <scene.rt>\n");
		return (1);
	}

	init_scene(&app.scene);
	read_rt_file(av[1], &app.scene);
	app.scene.win_width = 1920;
	app.scene.win_height = 1080;

	/* Render çözünürlüğü (bilinçli düşük) */
	app.scene.render_width = SCREEN_WIDTH;
	app.scene.render_height = SCREEN_HEIGHT;

	app.scene.aspect_ratio = (double)app.scene.render_width / (double)app.scene.render_height;
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, "miniRT");

	app.img.img = mlx_new_image(app.mlx, SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE);
	app.img.addr = mlx_get_data_addr(app.img.img, &app.img.bits_per_pixel,
									 &app.img.line_length, &app.img.endian);

	/* İlk çizim */
	redraw(&app);

	/* Hook’lar */
	mlx_key_hook(app.win, on_key, &app);
	mlx_hook(app.win, 17, 0, on_close, &app);

	mlx_loop(app.mlx);
	
	return (0);
}
