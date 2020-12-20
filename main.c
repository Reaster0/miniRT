#include "includes/minirt.h"

int key_hook(int keycode, t_vars vars)
{
	printf("Hello from key_hook!\n");
	return (1);
}

int main(void)
{
	t_vars vars;
	t_data img;
	int y = 640;
	int x = 480;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, y, x, "this is a test");

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}

void pixel_square(t_data *img, int y, int x, int sx, int sy, int color)
{
	int temp;
	int i;
	int j;
	i = 0;
	j = 0;
	temp = 0;
	while (i++ <= sy)
	{
		while (j++ <= sx)
		{
			mlx_pixel_put_fast(img, x++, y, color);
		}
		y++;
	}
}

void mlx_pixel_put_fast(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}