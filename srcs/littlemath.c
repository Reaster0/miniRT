/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   littlemath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:23:19 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 16:04:13 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d	add_product(t_3d a, t_3d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_3d	sub_product(t_3d a, t_3d b)
{
	t_3d ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_ray	calculate(t_ray ray, float t)
{
	t_ray temp;

	temp = ray;
	temp.endpoint = add_product(multiply_v(t, ray.endpoint), ray.startpoint);
	return (temp);
}
