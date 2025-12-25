/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:12:33 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 17:13:19 by msengul          ###   ########.fr       */
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
	render(&app->img, &app->scene);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
}

static void init_app_window(t_app *app)
{
    app->mlx = mlx_init();
    // Artık sabit WIN_WIDTH ve WIN_HEIGHT kullanıyoruz, çarpma işlemi yok
    app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
    app->img.img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
    app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel,
            &app->img.line_length, &app->img.endian);
}

static void setup_scene_render(t_app *app, char *filename)
{
    init_scene(&app->scene);
    read_rt_file(filename, &app->scene);

    // Başlangıç: Düşük Çözünürlük (Hızlı)
    app->scene.scale = 10;
    app->scene.render_width = WIN_WIDTH / 10;  // 160
    app->scene.render_height = WIN_HEIGHT / 10; // 90
    
    // Aspect ratio pencerenin gerçek oranına göre olmalı (1600/900 = 1.77)
    // 160/90 da aynı oranı verir, bu yüzden bozulma olmaz.
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
	init_app_window(&app);
	redraw(&app);
	mlx_key_hook(app.win, on_key, &app);
	mlx_hook(app.win, 17, 0, on_close, &app);
	mlx_loop(app.mlx);
	return (0);
}
