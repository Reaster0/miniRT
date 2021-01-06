#include "../includes/minirt.h"

void ft_putstr_fd(char *s, int fd)
{
	size_t i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void img_adress(t_data *data)
{
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								   &data->endian);
}

t_data new_img(t_vars *vars, int y, int x)
{
	t_data img;
	img.img = mlx_new_image(vars->mlx, x, y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	return (img);
}

int next_frame(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	mlx_destroy_image(vars->mlx, vars->data->img);
	return (1);
}

void pixel_square(t_data *data, int y, int x, int sx, int sy, int color)
{
	int temp;
	int i;
	int j;
	i = 0;
	temp = x;
	while (i++ <= sy)
	{
		j = 0;
		x = temp;
		while (j++ <= sx && x < 640)
		{
			mlx_pixel_put_fast(data, x++, y, color);
		}
		y++;
	}
}

int main(void)
{
	t_vars vars;
	t_data img;
	int y = 480;
	int x = 640;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, x, y, "Hello World!");
	img = new_img(&vars, 640, 480);
	pixel_square(&img, 0, 0, 50, 50, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_loop_hook(vars.mlx, next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
void mlx_pixel_put_fast(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
