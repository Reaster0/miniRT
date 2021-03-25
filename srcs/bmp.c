/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:00:51 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/25 14:30:10 by earnaud          ###   ########.fr       */
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

void save_image(t_data *img, t_2d wh)
{
	int div[7];
	div[0] = open("export.bmp", O_RDWR | O_TRUNC | O_CREAT, 0777);
	//maybe +4;
	div[1] = wh.x;
	div[2] = wh.y;
	div[3] = div[1] * div[2];
	div[4] = 54 + 4 * (int)wh.x * (int)wh.y;

	write(div[0], "BM", 2);
	write(div[0], &div[4], 4);
	write(div[0], "\0\0\0\0", 4);
	write(div[0], (char *)54, 1);
	//write(div[0], "\0\0\0\0", 4);
	write(div[0], (char *)40, 1);
	write(div[0], &div[1], 4);
	write(div[0], &div[2], 4);
	write(div[0], (char *)1, 2);
	write(div[0], &img->bits_per_pixel, 2);
	write(div[0], "\0\0\0\0", 4);
	write(div[0], &div[3], 4);
	write(div[0], "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
	div[5] = 0;
	while (div[5] < div[2])
	{
		div[6] = 0;
		while (div[6] < div[1])
		{
			int temp = 255;
			write(div[0], &temp, 4);
			//write(div[0], get_pixel(img, div[6], div[5]), 4);
			div[6]++;
		}
		div[5]++;
	}
}

int export(t_shapes *shapes, t_all *all, t_data *img, t_vars *vars)
{
	if (!set_start(all, &img, shapes))
		return (0);
	process_fullinter(all->vars, img, all, shapes);
	printf("\nsaving the image captain");
	save_image(img, *all->img_xy);
	return (1);
}
