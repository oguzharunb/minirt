#ifndef MINIRT_H
# define MINIRT_H


#define SCALE 4
# define SCREEN_WIDTH 320
# define SCREEN_HEIGHT 180
# include "camera.h"
# include "objects.h"

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}		t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void render(t_data *img, t_scene *scene);

#endif