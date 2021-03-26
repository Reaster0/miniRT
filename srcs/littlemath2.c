/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   littlemath2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:01:16 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 16:02:20 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	sqr(float number)
{
	return (number * number);
}

float	length2(t_3d point)
{
	return (sqr(point.x) + sqr(point.y) + sqr(point.z));
}

float	get_normf(float n)
{
	return (n /= sqrt(sqr(n)));
}

void	normalize2d(t_2d *vector)
{
	float norm;

	norm = sqrt(vector->x * vector->x + vector->y * vector->y);
	if (norm)
	{
		vector->x /= norm;
		vector->y /= norm;
	}
	else
	{
		vector->x = 0;
		vector->y = 0;
	}
}

void	normalize(t_3d *vector)
{
	float norm;

	norm = sqrt(sqr(vector->x) + sqr(vector->y) + sqr(vector->z));
	if (norm)
	{
		vector->x /= norm;
		vector->y /= norm;
		vector->z /= norm;
	}
	else
	{
		vector->x = 0;
		vector->y = 0;
		vector->z = 0;
	}
}
