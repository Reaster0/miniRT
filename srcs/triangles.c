/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:53:13 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/16 15:47:45 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//problemes sur les triangles qui sont derrieres la camera

static int in_it(t_ray *ray, t_triangle *triangle, float *t, t_3d *normal)
{
	t_3d edge1;
	t_3d edge2;
	float dDotN;

	edge1 = sub_product(triangle->b, triangle->a);
	edge2 = sub_product(triangle->c, triangle->a);
	*normal = cross_product(edge1, edge2);
	normalize(normal);
	if (dot_product(ray->endpoint, *normal) > 0.f)
		*normal = multiply_v(-1.f, *normal);
	dDotN = dot_product(ray->endpoint, *normal);
	if (dDotN == 0.f)
		return (0);
	*t = dot_product(sub_product(triangle->a, ray->startpoint), *normal) / dDotN;
	if (*t <= 0.000001f || *t >= ray->t)
		return (0);
	return (1);
}

int inter_triangle2(t_ray *ray, t_triangle *triangle)
{
	float area[3];
	t_3d interp;
	t_3d normal;
	float t;
	if (!in_it(ray, triangle, &t, &normal) || t <= 0.000001f || t >= ray->t)
		return (0);
	interp = add_product(multiply_v(t, ray->endpoint), ray->startpoint);
	area[0] = dot_product(normal, cross_product(sub_product(triangle->b, triangle->a), sub_product(triangle->c, triangle->a)));
	area[1] = dot_product(normal, cross_product(sub_product(triangle->b, interp), sub_product(triangle->c, interp)));
	triangle->bary.x = area[1] / area[0];
	if (triangle->bary.x > 1.f || triangle->bary.x < 0.f)
		return (0);
	area[2] = dot_product(normal, cross_product(sub_product(triangle->c, interp), sub_product(triangle->a, interp)));
	triangle->bary.y = area[2] / area[0];
	if (triangle->bary.y > 1.f || triangle->bary.y < 0.f)
		return (0);
	triangle->bary.z = 1.f - triangle->bary.x - triangle->bary.y;
	if (triangle->bary.z > 1.f || triangle->bary.z < 0.f)
		return (0);
	ray->shape_point = divide_vr(3, add_product(add_product(triangle->a, triangle->b), triangle->c));
	ray->t = t;
	ray->shape_color = triangle->color;
	ray->shape_normale = normal;
	return (1);
}

int inter_triangles(t_ray *ray, t_triangle *triangle)
{
	int i = 0;
	int ret;
	ret = 0;
	while (triangle)
	{
		if (inter_triangle2(ray, triangle))
			ret = 1;
		triangle = triangle->next;
	}
	return (ret);
}