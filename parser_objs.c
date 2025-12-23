/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:26:24 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 17:28:56 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sp;
	char		**split;
	t_sphere	*tmp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		exit_error("Malloc error", scene);
	split = ft_split(line, ' ');
	if (!split[1] || !split[2] || !split[3])
	{
		free(sp);
		free_split(split);
		exit_error("Missing Sphere parameters", scene);
	}
	sp->center = parse_vec3(split[1], scene);
	sp->radius = ft_atof(split[2]) / 2.0;
	sp->color = parse_rgb(split[3], scene);
	sp->next = NULL;
	free_split(split);
	if (!scene->spheres)
		scene->spheres = sp;
	else
	{
		tmp = scene->spheres;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = sp;
	}
}

void	parse_plane(char *line, t_scene *scene)
{
	t_plane	*pl;
	char	**split;
	t_plane	*tmp;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		exit_error("Malloc error", scene);
	split = ft_split(line, ' ');
	if (!split[1] || !split[2] || !split[3])
	{
		free(pl);
		free_split(split);
		exit_error("Missing Plane parameters", scene);
	}
	pl->point = parse_vec3(split[1], scene);
	pl->normal = vec_normalize(parse_vec3(split[2], scene));
	pl->color = parse_rgb(split[3], scene);
	pl->next = NULL;
	free_split(split);
	if (!scene->planes)
		scene->planes = pl;
	else
	{
		tmp = scene->planes;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = pl;
	}
}

void	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cy;
	char		**split;
	t_cylinder	*tmp;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		exit_error("Malloc error", scene);
	split = ft_split(line, ' ');
	if (!split[1] || !split[2] || !split[3] || !split[4] || !split[5])
	{
		free(cy);
		free_split(split);
		exit_error("Missing Cylinder parameters", scene);
	}
	cy->center = parse_vec3(split[1], scene);
	cy->axis = vec_normalize(parse_vec3(split[2], scene));
	cy->radius = ft_atof(split[3]) / 2.0;
	cy->height = ft_atof(split[4]);
	cy->color = parse_rgb(split[5], scene);
	cy->next = NULL;
	free_split(split);
	if (!scene->cylinders)
		scene->cylinders = cy;
	else
	{
		tmp = scene->cylinders;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cy;
	}
}
