/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/07 17:16:43 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(void)
{
	t_vars vars;
	t_data img;
	int y = 480;
	int x = 640;
	vars.mlx = mlx_init();
	ft_putstr_fd("ceci est un test", 1);
	vars.win = mlx_new_window(vars.mlx, x, y, "Hello World!");
	img = new_img(&vars, 640, 480);
	pixel_square(&img, 0, 0, 50, 50, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_loop_hook(vars.mlx, next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
