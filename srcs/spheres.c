/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:54:29 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/12 11:28:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int inter_sphere(t_ray *ray, t_sphere *sphere)
{
	float a;
	float b;
	float c;
	float d;
	float discriminant;
	float t1;
	float t2;
	t_3d l = sub_product(ray->startpoint, sphere->startpoint);

	a = dot_product(ray->endpoint, ray->endpoint);
	b = 2.f * dot_product(ray->endpoint, l);
	c = dot_product(l, l) - sqr(sphere->r);
	discriminant = sqr(b) - 4 * a * c;
	if (discriminant < 0.0f)
		return (0);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 > 0.0001f && t1 < ray->t)
		ray->t = t1;
	else if (t2 > 0.0001f && t2 < ray->t)
		ray->t = t2;
	else
		return (0);

	ray->shape_point = sphere->startpoint;
	ray->shape_color = sphere->color;

	ray->shape_normale = sub_product(ray->startpoint, sphere->startpoint);
	normalize(&ray->shape_normale);
	return (1);
}

int inter_spheres(t_ray *ray, t_sphere *sphere)
{
	int i = 0;
	int ret;
	ret = 0;
	while (sphere)
	{
		if (inter_sphere(ray, sphere))
			ret = 1;
		sphere = sphere->next;
	}
	return (ret);
}