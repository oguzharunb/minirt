/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:27:40 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 18:00:09 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parser.h"
#include <unistd.h>

void	exit_error(char *msg, t_scene *scene)
{
	printf("Error\n%s\n", msg);
	if (scene)
		free_scene(scene);
	exit(1);
}

void	init_scene(t_scene *scene)
{
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->amb.ratio = -1.0;
	scene->light.ratio = -1.0;
}

static void	parse_id(char *line, t_scene *scene, int i)
{
	i = skip_whitespace(line, 0);
	if (!line[i] || line[i] == '#')
		return ;
	if (line[i] == 'A' && line[i + 1] == ' ')
		parse_ambient(line + i, scene);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		parse_camera(line + i, scene);
	else if (line[i] == 'L' && line[i + 1] == ' ')
		parse_light(line + i, scene);
	else if (line[i] == 's' && line[i + 1] == 'p' && line[i + 2] == ' ')
		parse_sphere(line + i, scene);
	else if (line[i] == 'p' && line[i + 1] == 'l' && line[i + 2] == ' ')
		parse_plane(line + i, scene);
	else if (line[i] == 'c' && line[i + 1] == 'y' && line[i + 2] == ' ')
		parse_cylinder(line + i, scene);
	else
		exit_error("Unknown identifier", scene);
}

static void	parse_line(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	i = skip_whitespace(line, 0);
	if (!line[i] || line[i] == '#')
		return ;
	parse_id(line, scene, i);
}

void	read_rt_file(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open file", NULL);
	init_scene(scene);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\0' && line[0] != '\n')
			parse_line(line, scene);
		free(line);
	}
	close(fd);
	if (scene->amb.ratio == -1.0)
		exit_error("Missing Ambient Light (A)", scene);
	if (scene->light.ratio == -1.0)
		exit_error("Missing Light (L)", scene);
}
