/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:24:23 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 17:41:58 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

double	ft_atof(char *str)
{
	double	res;
	double	factor;
	int		sign;
	int		i;

	res = 0.0;
	factor = 1.0;
	sign = 1;
	i = 0;
	if (!str)
		return (0.0);
	if (str[i] == '-' && ++i)
		sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + (str[i++] - '0');
			factor *= 10.0;
		}
	}
	return (res / factor * sign);
}

t_vec3	parse_vec3(char *str, t_scene *scene)
{
	t_vec3	vec;
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_split(split);
		exit_error("Invalid vector format", scene);
	}
	vec.x = ft_atof(split[0]);
	vec.y = ft_atof(split[1]);
	vec.z = ft_atof(split[2]);
	free_split(split);
	return (vec);
}

t_rgb	parse_rgb(char *str, t_scene *scene)
{
	t_rgb	c;
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_split(split);
		exit_error("Invalid color format", scene);
	}
	c.r = ft_atoi(split[0]);
	c.g = ft_atoi(split[1]);
	c.b = ft_atoi(split[2]);
	free_split(split);
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
		exit_error("Color values must be in [0-255]", scene);
	return (c);
}

int	skip_whitespace(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
			|| line[i] == '\r'))
		i++;
	return (i);
}
