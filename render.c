#include "camera.h"
#include "color.h"
#include "minirt.h"
#include "objects.h"
#include "ray.h"
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_data *data, t_camera *cam)
{
	int			i;
	int			j;
	t_ray		ray;        
	t_sphere	*sphere;

	sphere = create_sphere(1.0, 0.0, 0.0, 0.0);

	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		for (j = 0; j < SCREEN_HEIGHT; j++)
		{
			set_ray(&ray, cam, i, j);             

			if (hit_sphere(sphere, &ray))          
				my_mlx_pixel_put(data, i, j, 0xFFFFFF);
			else
				my_mlx_pixel_put(data, i, j, 0x000000);
		}
	}
}
