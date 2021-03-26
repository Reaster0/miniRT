/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   littlemath3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:01:19 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 16:03:12 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d	get_norm(t_3d vector)
{
	float norm;

	norm = sqrt(sqr(vector.x) + sqr(vector.y) + sqr(vector.z));
	if (norm)
	{
		vector.x /= norm;
		vector.y /= norm;
		vector.z /= norm;
	}
	else
	{
		vector.x = 0;
		vector.y = 0;
		vector.z = 0;
	}
	return (vector);
}

t_3d	multiply_v(float a, t_3d vector)
{
	vector.x *= a;
	vector.y *= a;
	vector.z *= a;
	return (vector);
}

void	divide_v(float a, t_3d *vector)
{
	if (a)
	{
		vector->x /= a;
		vector->y /= a;
		vector->z /= a;
	}
}

t_3d	divide_vr(float a, t_3d vector)
{
	if (a)
	{
		vector.x /= a;
		vector.y /= a;
		vector.z /= a;
	}
	return (vector);
}

t_3d	sub_vr(float a, t_3d vector)
{
	vector.x -= a;
	vector.y -= a;
	vector.z -= a;
	return (vector);
}
