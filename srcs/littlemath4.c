/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   littlemath4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:04:46 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 16:04:48 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	sub_v(float a, t_3d *vector)
{
	vector->x -= a;
	vector->y -= a;
	vector->z -= a;
}

t_3d	add_v(float a, t_3d vector)
{
	vector.x += a;
	vector.y += a;
	vector.z += a;
	return (vector);
}

t_3d	multiply_product(t_3d a, t_3d b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

float	dot_product(t_3d a, t_3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_3d	cross_product(t_3d a, t_3d b)
{
	t_3d ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}
