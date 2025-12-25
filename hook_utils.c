/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:53:18 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 13:54:58 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	switch_to_low_res(t_scene *scene)
{
	if (scene->scale != 10)
	{
		scene->scale = 10;
		scene->render_width = WIN_WIDTH / 10;
		scene->render_height = WIN_HEIGHT / 10;
	}
}

void	switch_to_high_res(t_scene *scene)
{
	if (scene->scale != 1)
	{
		scene->scale = 1;
		scene->render_width = WIN_WIDTH;
		scene->render_height = WIN_HEIGHT;
	}
}
