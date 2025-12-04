#include "camera.h"
#include "color.h"
#include "minirt.h"
#include "ray.h"
#include <stdlib.h>

// Görüntü buffer'ına piksel yazan yardımcı fonksiyon
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_data *data, t_camera *cam)
{
    
	int i;
	int j;
    t_ray *ray;
    
    i = 0;
    ray = init_ray();
    if (!ray)
        return ;
        
    (void) cam;
	while (i < SCREEN_WIDTH)
	{

		j = 0;
		while (j < SCREEN_HEIGHT)
		{
            set_ray(ray, i, j);
			my_mlx_pixel_put(data, i, j, 0xFFFFFF);
            print_ray(ray);
			j++;
		}
		i++;
	}
}


