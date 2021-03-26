/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:00:51 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 11:39:38 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <fcntl.h>

int check_error(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "--save", 6) != 0)
	{
		printf("Error\nargument must be save, captain");
		return (0);
	}
	return (1);
}

int set_start(t_all *all, t_data **img, t_shapes *shapes)
{
	all->nbr_img = nbr_cam(shapes->camera);
	all->i = 0;
	all->vars->mlx = mlx_init();
	*img = malloc(sizeof(t_data) * (all->nbr_img + 1));
	if (!*img)
		return (0);
	all->img_xy = malloc(sizeof(t_2d) * (all->nbr_img + 1));
	if (!all->img_xy)
		return (0);
	all->img = *img;
}

void file_header(int fd, t_2d wh)
{
	int size;
	int offset;
	int sizeall;

	offset = 54;
	sizeall = (54 + (int)wh.x * (int)wh.y * 4) + ((int)wh.x % 4) * (int)wh.x;
	write(fd, "BM", 2);
	write(fd, &sizeall, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &offset, 4);
}

void info_header(int fd, t_2d wh, t_data *img)
{
	int values[5];

	values[0] = wh.x;
	values[1] = wh.y;
	values[2] = 40;
	values[3] = (int)wh.x * (int)wh.y * 4;
	values[4] = 1;
	write(fd, &values[2], 4);
	write(fd, &values[0], 4);
	write(fd, &values[1], 4);
	write(fd, &values[4], 2);
	write(fd, &img->bits_per_pixel, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &values[3], 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

int save_image(t_data *img, t_2d wh)
{
	int fd;
	int temp;
	unsigned char color[3];
	int extrabytes;
	fd = open("export.bmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0);
	file_header(fd, wh);
	info_header(fd, wh, img);
	while ((int)wh.y)
	{
		temp = 0;
		while (temp < (int)wh.x)
		{
			color[0] = get_b(*(int *)get_pixel(img, temp, wh.y));
			color[1] = get_g(*(int *)get_pixel(img, temp, wh.y));
			color[2] = get_r(*(int *)get_pixel(img, temp, wh.y));
			write(fd, color, 3);
			write(fd, "\0", 1);
			temp++;
		}
		wh.y--;
	}
	return (1);
}

int export_bmp(t_shapes *shapes, t_all *all, t_data *img, t_vars *vars)
{
	if (!set_start(all, &img, shapes))
		return (0);
	process_fullinter(all->vars, img, all, shapes);
	printf("\nsaving the image captain");
	return (save_image(img, *all->img_xy));
}
