/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:55:28 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/15 21:51:21 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_triangle new_triangle(t_3d a, t_3d b, t_3d c, int color)
{
	t_triangle triangle;
	triangle.a = a;
	triangle.b = b;
	triangle.c = c;
	triangle.color = color;
	triangle.next = NULL;
	return (triangle);
}

static int in_it(t_ray *ray, t_square *square, float *t)
{
	float dDotN;

	if (dot_product(ray->endpoint, square->orient) > 0.f)
		square->orient = multiply_v(-1.f, square->orient);
	dDotN = dot_product(ray->endpoint, square->orient);
	if (dDotN == 0.f)
		return (0);
	*t = dot_product(sub_product(square->center, ray->startpoint), square->orient) / dDotN;
	if (*t <= 0.000001f || *t >= ray->t)
		return (0);
	return (1);
}

int square_len(t_square *square, t_3d interp)
{
	t_3d temp;
	if (interp.x < 0.f)
		interp.x *= -1.f;
	if (interp.y < 0.f)
		interp.y *= -1.f;
	temp = sub_product(interp, square->center);

	if (temp.x > square->side / 2 || temp.y > square->side / 2)
		return (0);

	return (1);
}

int inter_square(t_ray *ray, t_square *square)
{
	float t;
	t_3d interp;

	if (!in_it(ray, square, &t))
		return (0);
	interp = add_product(multiply_v(t, ray->endpoint), ray->startpoint);
	if (!square_len(square, interp))
		return (0);
	ray->shape_color = square->color;
	ray->t = t;
	ray->shape_normale = square->orient;
	return (1);

	// int result;
	// t_3d point[4];
	// point[0].x = square->center.x - square->side / 2;
	// point[0].y = square->center.y - square->side / 2;
	// point[1].x = square->center.x + square->side / 2;
	// point[1].y = square->center.y - square->side / 2;
	// point[2].x = square->center.x + square->side / 2;
	// point[2].y = square->center.y + square->side / 2;
	// point[3].x = square->center.x - square->side / 2;
	// point[3].y = square->center.y + square->side / 2;

	// t_triangle triangle1;
	// t_triangle triangle2;
	// result = 0;
	// triangle1 = new_triangle(point[0], point[1], point[2], square->color);
	// triangle2 = new_triangle(point[0], point[2], point[3], square->color);
	// if (inter_triangle2(ray, &triangle1))
	// 	result = (1);
	// if (inter_triangle2(ray, &triangle2))
	// 	result = (1);
	// if (result == 1)
	// {
	// 	ray->shape_point = sub_product(point[2], divide_vr(2, point[0]));
	// 	return (result);
	// }
}

int inter_squares(t_ray *ray, t_square *square)
{
	int ret;
	ret = 0;
	while (square)
	{
		if (inter_square(ray, square))
			ret = 1;
		square = square->next;
	}
	return (ret);
}