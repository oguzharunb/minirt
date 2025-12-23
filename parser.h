/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:23:52 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 18:12:20 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"
# include "objects.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

/* parser.c */
void	read_rt_file(char *filename, t_scene *scene);
void	init_scene(t_scene *scene);
void	exit_error(char *msg, t_scene *scene);

/* parser_scene.c */
void	parse_ambient(char *line, t_scene *scene);
void	parse_camera(char *line, t_scene *scene);
void	parse_light(char *line, t_scene *scene);

/* parser_objs.c */
void	sphere_add_back(t_sphere **lst, t_sphere *new);
void	plane_add_back(t_plane **lst, t_plane *new);
void	cylinder_add_back(t_cylinder **lst, t_cylinder *new);
void	parse_sphere(char *line, t_scene *scene);
void	parse_plane(char *line, t_scene *scene);
void	parse_cylinder(char *line, t_scene *scene);

/* parser_utils.c */
double	ft_atof(char *str);
t_vec3	parse_vec3(char *str, t_scene *scene);
t_rgb	parse_rgb(char *str, t_scene *scene);
void	free_split(char **split);
int		skip_whitespace(char *line, int i);

#endif