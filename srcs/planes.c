/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:37:44 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/16 14:24:07 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		inter_plane(t_ray *ray, t_plane *plane)
{
	float ddotn;
	float t;

	if (dot_product(ray->endpoint, plane->normal) > 0.f)
		plane->normal = multiply_v(-1.f, plane->normal);
	ddotn = dot_product(ray->endpoint, plane->normal);
	if (ddotn == 0.f)
		return (0);
	t = dot_product(sub_product(plane->position,
				ray->startpoint), plane->normal) / ddotn;
	if (t <= 0.000001f || t >= ray->t)
		return (0);
	ray->shape_color = plane->color;
	ray->t = t;
	ray->shape_point = plane->position;
	ray->shape_normale = plane->normal;
	return (1);
}

int		inter_planes(t_ray *ray, t_plane *plane)
{
	int ret;

	ret = 0;
	while (plane)
	{
		if (inter_plane(ray, plane))
			ret = 1;
		plane = plane->next;
	}
	return (ret);
}
