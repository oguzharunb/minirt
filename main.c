#include "mlx.h"
#include "minirt.h"
#include "objects.h"
#include <stdlib.h>


typedef struct s_data {
    void    *img;          // mlx_new_image tarafından döndürülen işaretçi
    char    *addr;         // Görüntü verisinin başlangıç adresi
    int     bits_per_pixel; // Bir piksel için gereken bit sayısı (genellikle 32)
    int     line_length;    // Bir yatay çizginin byte cinsinden uzunluğu
    int     endian;         // Byte sırası (büyük/küçük)
} t_data;

// Görüntü buffer'ına piksel yazan yardımcı fonksiyon
void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
int main(void)
{
    void    *mlx;
    void    *win;
	t_data	img;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Merhaba MiniLibX!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//my_mlx_pixel_put(&img, 0, 0, 0xFFFFFFFF);

	t_sphere	*my_sphere = create_sphere(1, 0, 0, 0);

	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
    mlx_loop(mlx);

    return (0);
}
