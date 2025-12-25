/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:12:33 by msengul           #+#    #+#             */
/*   Updated: 2025/12/25 17:51:56 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "objects.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	redraw(t_app *app)
{
	render(app);
}

static int	init_app_window(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (1);
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!app->win)
	{
		mlx_destroy_display(app->mlx);
		return (1);
	}
	app->img.img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!app->img.img)
	{
		mlx_destroy_window(&app->mlx, &app->win);
		mlx_destroy_display(&app->mlx);
		return (1);
	}
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel,
			&app->img.line_length, &app->img.endian);
	return (0);
}

static void	setup_scene_render(t_app *app, char *filename)
{
	init_scene(&app->scene);
	read_rt_file(filename, &app->scene);
	app->scene.scale = 10;
	app->scene.render_width = WIN_WIDTH / 10;
	app->scene.render_height = WIN_HEIGHT / 10;
	app->scene.aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
}

int	main(int ac, char **av)
{
	t_app	app;

	if (ac != 2)
	{
		printf("Error\nUsage: ./minirt <scene.rt>\n");
		return (1);
	}
	setup_scene_render(&app, av[1]);
	if (init_app_window(&app))
	{
		free_scene(&app.scene);
		printf("Error\n");
		return (1);
	}
	redraw(&app);
	mlx_key_hook(app.win, on_key, &app);
	mlx_hook(app.win, 17, 0, on_close, &app);
	mlx_loop(app.mlx);
	return (0);
}
