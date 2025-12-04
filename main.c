#include "camera.h"
#include "minirt.h"
#include "mlx.h"
#include "objects.h"
#include <stdlib.h>

int	main(void)
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_camera	*camera;
	t_sphere	*sphere;

	mlx = mlx_init();
	win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Merhaba MiniLibX!");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	// my_mlx_pixel_put(&img, 0, 0, 0xFFFFFFFF);
	camera = init_camera();
	sphere = create_sphere(1.0, 0.0, 0.0, 0.0);
	render(&img, camera);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
