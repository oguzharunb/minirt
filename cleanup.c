/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:05:14 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 17:06:51 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>

void	free_objects(t_scene *scene)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	void		*tmp;

	sp = scene->spheres;
	while (sp)
	{
		tmp = sp->next;
		free(sp);
		sp = tmp;
	}
	pl = scene->planes;
	while (pl)
	{
		tmp = pl->next;
		free(pl);
		pl = tmp;
	}
	cy = scene->cylinders;
	while (cy)
	{
		tmp = cy->next;
		free(cy);
		cy = tmp;
	}
}

void	free_scene(t_scene *scene)
{
	free_objects(scene);
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}

int	on_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app->img.img)
		mlx_destroy_image(app->mlx, app->img.img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	free_scene(&app->scene);
	exit(0);
	return (0);
}
