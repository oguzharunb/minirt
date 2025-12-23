#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"
# include "get_next_line.h"
# include "objects.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "color.h"

void    exit_error(char *msg, t_scene *scene);
void    free_scene(t_scene *scene);
double  ft_atof(char *str);
t_vec3  parse_vec3(char *str);
t_rgb parse_color(char *str);
int     skip_whitespace(char *line, int i);
void    parse_ambient(char *line, t_scene *scene);
void    parse_camera(char *line, t_scene *scene);
void    parse_light(char *line, t_scene *scene);
void    parse_sphere(char *line, t_scene *scene);
void    parse_plane(char *line, t_scene *scene);
void    parse_cylinder(char *line, t_scene *scene);
void    init_scene(t_scene *scene);
void    read_rt_file(char *filename, t_scene *scene);
void    write_rt_file(t_scene *scene);

#endif