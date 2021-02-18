/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:37:44 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/18 13:26:07 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int inter_plane(t_ray *ray, t_plane *plane)
{
	float dDotN;
	float t;
	if (dot_product(ray->endpoint, plane->normal) > 0.f)
		plane->normal = multiply_v(-1, plane->normal);
	dDotN = dot_product(ray->endpoint, plane->normal);
	if (dDotN == 0.f)
		return (0);

	t = dot_product(sub_product(plane->position, ray->startpoint), plane->normal) / dDotN;
	if (t <= 0.000001f || t >= ray->t)
		return (0);

	//ray->color = plane->color;

	ray->shape_color = plane->color;
	ray->t = t;
	ray->shape_point = plane->position;
	ray->shape_normale = plane->normal;
	return (1);
}

int inter_planes(t_ray *ray, t_plane **plane)
{
	int i = 0;
	int ret;
	ret = 0;
	while (plane[i])
	{
		if (inter_plane(ray, plane[i]))
			ret = 1;
		i++;
	}
	return (ret);
}