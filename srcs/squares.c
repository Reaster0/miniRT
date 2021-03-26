/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:55:28 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/17 14:17:20 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	in_it(t_ray *ray, t_square *square, float *t)
{
	float ddotn;

	if (dot_product(ray->endpoint, square->orient) > 0.f)
		square->orient = multiply_v(-1.f, square->orient);
	ddotn = dot_product(ray->endpoint, square->orient);
	if (ddotn == 0.f)
		return (0);
	*t = dot_product(sub_product(square->center, ray->startpoint),
			square->orient) / ddotn;
	if (*t <= 0.000001f || *t >= ray->t)
		return (0);
	return (1);
}

int			square_len(t_square *square, t_3d *interp)
{
	t_3d temp;

	temp = sub_product(*interp, square->center);
	if (fabs(temp.x) >= square->side / 2 || fabs(temp.y) >= square->side / 2
			|| fabs(temp.z) >= square->side / 2)
		return (0);
	return (1);
}

int			inter_square(t_ray *ray, t_square *square)
{
	float	t;
	t_3d	interp;

	if (!in_it(ray, square, &t))
		return (0);
	interp = add_product(multiply_v(t, ray->endpoint), ray->startpoint);
	if (!square_len(square, &interp))
		return (0);
	if (t >= ray->t || t <= 0.0001f)
		return (0);
	ray->shape_color = square->color;
	ray->shape_point = square->center;
	ray->t = t;
	ray->shape_normale = square->orient;
	return (1);
}

int			inter_squares(t_ray *ray, t_square *square)
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
