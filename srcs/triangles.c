/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:53:13 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/09 16:34:25 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//problemes sur les triangles qui sont derrieres la camera
int inter_triangle(t_ray *ray, t_triangle *triangle)
{
	t_3d edge1;
	t_3d edge2;
	t_3d orig_minus_vert0;
	t_3d cross_raydir_edge2;
	t_3d cross_oriminusvert0_edge1;
	float determinent, inv_determinent;
	float t;

	edge1 = sub_product(triangle->b, triangle->a);
	edge2 = sub_product(triangle->c, triangle->a);

	cross_raydir_edge2 = cross_product(ray->endpoint, edge2);
	determinent = dot_product(edge1, cross_raydir_edge2);

	if (determinent > -0.000001f && determinent < 0.000001f)
		return (0);
	inv_determinent = 1.0f / determinent;

	orig_minus_vert0 = sub_product(ray->startpoint, triangle->a);

	triangle->barycentric.y = dot_product(orig_minus_vert0, cross_raydir_edge2) * inv_determinent;
	if (triangle->barycentric.y < 0.0f || triangle->barycentric.y > 1.0f)
		return (0);

	cross_oriminusvert0_edge1 = cross_product(orig_minus_vert0, edge1);

	triangle->barycentric.z = dot_product(ray->endpoint, cross_oriminusvert0_edge1) * inv_determinent;
	if (triangle->barycentric.z < 0.0f || triangle->barycentric.z > 1.0f)
		return (0);
	triangle->barycentric.x = 1 - triangle->barycentric.y - triangle->barycentric.z;

	if (triangle->barycentric.x < 0.0f || triangle->barycentric.z > 1.0f)
		return (0);

	t = dot_product(edge2, cross_oriminusvert0_edge1) * inv_determinent;
	if (t < ray->t)
	{
		ray->shape_normale = cross_product(sub_product(triangle->b, triangle->a), sub_product(triangle->c, triangle->a));
		ray->shape_point = new_3d((triangle->a.x + triangle->b.x + triangle->c.x) / 2, (triangle->a.y + triangle->b.y + triangle->c.y) / 2, (triangle->a.z + triangle->b.z + triangle->c.z) / 2);
		ray->t = t;

		ray->color = triangle->color;
		ray->shape_color = triangle->color;
	}
	return (1);
}

int inter_triangles(t_ray *ray, t_triangle *triangle)
{
	int i = 0;
	int ret;
	ret = 0;
	while (triangle)
	{
		if (inter_triangle(ray, triangle))
			ret = 1;
		triangle = triangle->next;
	}
	return (ret);
}