/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:55:28 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/17 20:56:12 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int inter_square(t_ray *ray, t_square *square)
{
	int result;

	t_triangle *triangle1;
	t_triangle *triangle2;
	result = 0;
	triangle1 = new_triangle(square->a, square->b, square->c, square->color);
	triangle2 = new_triangle(square->a, square->c, square->d, square->color);
	if (inter_triangle(ray, triangle1))
		result = (1);
	free(triangle1);
	if (inter_triangle(ray, triangle2))
		result = (1);
	free(triangle2);
	// if (result == 1)
	// {
	// 	//ray->shape_point = sub_product(square->c, divide_vr(2, square->a));
	// 	//ray->shape_normale = cross_product(sub_product(square->c, square->b), sub_product(square->a, square->b));
	// 	ray->shape_color = square->color;
	// }
	return (result);
}

int inter_squares(t_ray *ray, t_square **square)
{
	int i = 0;
	int ret;
	ret = 0;
	while (square[i])
	{
		if (inter_square(ray, square[i]))
			ret = 1;
		i++;
	}
	return (ret);
}