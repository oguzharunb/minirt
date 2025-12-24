/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:24:51 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 15:28:12 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

#define ASPECT_RATIO (16.0 / 9.0)

static void	setup_camera(t_camera *cam, double fov_deg)
{
	t_vec3	g_up;
	double	theta;
	double	h;

	theta = fov_deg * M_PI / 180.0;
	h = tan(theta / 2.0);
	cam->viewport_h = 2.0 * h;
	cam->viewport_w = ASPECT_RATIO * cam->viewport_h;
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

void	parse_ambient(char *line, t_scene *scene)
{
	char	**split;

	if (scene->amb.ratio != -1.0)
		exit_error("Multiple Ambient Light defined", scene);
	split = ft_split(line, ' ');
	if (!split[1] || !split[2])
	{
		free_split(split);
		exit_error("Missing Ambient parameters", scene);
	}
	scene->amb.ratio = ft_atof(split[1]);
	scene->amb.color = parse_rgb(split[2], scene);
	free_split(split);
	if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
		exit_error("Ambient ratio must be in range [0.0, 1.0]", scene);
}

void	parse_camera(char *line, t_scene *scene)
{
	char	**split;
	double	fov;

	split = ft_split(line, ' ');
	if (!split[1] || !split[2] || !split[3])
	{
		free_split(split);
		exit_error("Missing Camera parameters", scene);
	}
	scene->camera.origin = parse_vec3(split[1], scene);
	scene->camera.forward = parse_vec3(split[2], scene);
	fov = ft_atof(split[3]);
	free_split(split);
	if (fov < 0 || fov > 180)
		exit_error("Camera FOV must be in range [0, 180]", scene);
	setup_camera(&scene->camera, fov);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**split;

	if (scene->light.ratio != -1.0)
		exit_error("Multiple Lights defined", scene);
	split = ft_split(line, ' ');
	if (!split[1] || !split[2] || !split[3])
	{
		free_split(split);
		exit_error("Missing Light parameters", scene);
	}
	scene->light.position = parse_vec3(split[1], scene);
	scene->light.ratio = ft_atof(split[2]);
	scene->light.color = parse_rgb(split[3], scene);
	free_split(split);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		exit_error("Light ratio must be in range [0.0, 1.0]", scene);
}
