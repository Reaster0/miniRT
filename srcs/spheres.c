/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:54:29 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/16 14:20:32 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	solutions(t_ray *ray, t_sphere *sphere, t_2d *t)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_3d	l;

	l = sub_product(ray->startpoint, sphere->startpoint);
	a = dot_product(ray->endpoint, ray->endpoint);
	b = 2.f * dot_product(ray->endpoint, l);
	c = dot_product(l, l) - sqr(sphere->r);
	discriminant = sqr(b) - 4 * a * c;
	if (discriminant < 0.0f)
		return (0);
	t->x = (-b - sqrt(discriminant)) / (2 * a);
	t->y = (-b + sqrt(discriminant)) / (2 * a);
	return (1);
}

int			inter_sphere(t_ray *ray, t_sphere *sphere)
{
	t_2d t;

	if (!solutions(ray, sphere, &t))
		return (0);
	if (t.x > 0.0001f && t.x < ray->t)
		ray->t = t.x;
	else if (t.y > 0.0001f && t.y < ray->t)
		ray->t = t.y;
	else
		return (0);
	ray->shape_point = sphere->startpoint;
	ray->shape_color = sphere->color;
	ray->shape_normale = sub_product(ray->startpoint, sphere->startpoint);
	normalize(&ray->shape_normale);
	return (1);
}

int			inter_spheres(t_ray *ray, t_sphere *sphere)
{
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
