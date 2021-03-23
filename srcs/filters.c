/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:23:27 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/23 13:52:21 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void filter_psyche(t_vars *vars, t_data *data, t_2d *xy)
{
	t_2d count;
	count.y = 0;
	while (count.y < xy->y)
	{
		count.x = 0;
		while (count.x < xy->x)
		{
			*(int *)get_pixel(data, count.x, count.y) = add_shade(0.4, *(int *)get_pixel(data, count.x, count.y));
			count.x++;
		}
		count.y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, data->img, 0, 0);
}

void filter_invert(t_vars *vars, t_data *data, t_2d *xy)
{
	t_2d count;
	count.y = 0;
	while (count.y < xy->y)
	{
		count.x = 0;
		while (count.x < xy->x)
		{
			*(int *)get_pixel(data, count.x, count.y) = get_opposite(*(int *)get_pixel(data, count.x, count.y));
			count.x++;
		}
		count.y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, data->img, 0, 0);
}