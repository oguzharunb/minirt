/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:08:30 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 13:58:16 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static t_vec3	rot_axis(t_vec3 v, t_vec3 axis, double ang)
{
	double	c;
	double	s;

	c = cos(ang);
	s = sin(ang);
	axis = vec_normalize(axis);
	return (vec_add(vec_add(vec_mul(v, c), vec_mul(vec_cross(axis, v), s)),
			vec_mul(axis, vec_dot(axis, v) * (1.0 - c))));
}

static void	cam_rebuild(t_camera *cam)
{
	t_vec3	g_up;

	cam->forward = vec_normalize(cam->forward);
	g_up = vec(0, 1, 0);
	if (fabs(cam->forward.y) > 0.999)
		cam->right = vec_normalize(vec_cross(vec(0, 0, 1), cam->forward));
	else
		cam->right = vec_normalize(vec_cross(g_up, cam->forward));
	cam->up = vec_cross(cam->forward, cam->right);
	cam->horizontal = vec_mul(cam->right, cam->viewport_w);
	cam->vertical = vec_mul(cam->up, cam->viewport_h);
	cam->lower_left = vec_sub(cam->origin, vec_mul(cam->horizontal, 0.5));
	cam->lower_left = vec_sub(cam->lower_left, vec_mul(cam->vertical, 0.5));
	cam->lower_left = vec_add(cam->lower_left, cam->forward);
}

static void	handle_move(int key, t_camera *cam, int *changed)
{
	if (key == KEY_W || key == KEY_S || key == KEY_D || key == KEY_A
		|| key == KEY_SPACE || key == KEY_SHIFT)
	{
		if (key == KEY_W)
			cam->origin = vec_add(cam->origin, vec_mul(cam->forward,
						MOVE_STEP));
		else if (key == KEY_S)
			cam->origin = vec_sub(cam->origin, vec_mul(cam->forward,
						MOVE_STEP));
		else if (key == KEY_D)
			cam->origin = vec_add(cam->origin, vec_mul(cam->right, MOVE_STEP));
		else if (key == KEY_A)
			cam->origin = vec_sub(cam->origin, vec_mul(cam->right, MOVE_STEP));
		else if (key == KEY_SPACE)
			cam->origin = vec_add(cam->origin, vec_mul(cam->up, MOVE_STEP));
		else if (key == KEY_SHIFT)
			cam->origin = vec_sub(cam->origin, vec_mul(cam->up, MOVE_STEP));
		*changed = 1;
	}
}

static void	handle_rotate(int key, t_camera *cam, int *changed)
{
	t_vec3	new_f;

	if (key == KEY_LEFT)
		cam->forward = rot_axis(cam->forward, vec(0, 1, 0), ROT_STEP);
	else if (key == KEY_RIGHT)
		cam->forward = rot_axis(cam->forward, vec(0, 1, 0), -ROT_STEP);
	else if (key == KEY_UP || key == KEY_DOWN)
	{
		if (key == KEY_UP)
			new_f = rot_axis(cam->forward, cam->right, ROT_STEP);
		else
			new_f = rot_axis(cam->forward, cam->right, -ROT_STEP);
		if (fabs(vec_dot(vec_normalize(new_f), vec(0, 1, 0))) < 0.999)
			cam->forward = new_f;
	}
	else
		return ;
	*changed = 1;
}

int	on_key(int key, void *param)
{
	t_app	*app;
	int		changed;

	app = (t_app *)param;
	changed = 0;
	if (key == KEY_ESC)
		on_close(app);
	if (key == KEY_R)
	{
		switch_to_high_res(&app->scene);
		redraw(app);
		return (0);
	}
	if (key == KEY_W || key == KEY_S || key == KEY_D || key == KEY_A
		|| key == KEY_SPACE || key == KEY_SHIFT || key == KEY_UP
		|| key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)
		switch_to_low_res(&app->scene);
	handle_move(key, &app->scene.camera, &changed);
	handle_rotate(key, &app->scene.camera, &changed);
	if (changed)
	{
		cam_rebuild(&app->scene.camera);
		redraw(app);
	}
	return (0);
}
