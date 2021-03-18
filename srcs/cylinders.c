/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:56:24 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/18 17:01:15 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int inside_cyl(t_cylinder *cylinder, t_ray *ray, float t)
{
	t_3d hitpoint;
	t_3d bottom;
	t_3d top;
	cylinder->pointup = add_product(cylinder->point, multiply_v(cylinder->height, cylinder->orient));
	hitpoint = add_product(ray->startpoint, multiply_v(t, ray->endpoint));
	bottom = sub_product(hitpoint, cylinder->point);
	top = sub_product(hitpoint, cylinder->pointup);

	if (dot_product(cylinder->orient, bottom) > 0.0 && dot_product(cylinder->orient, top) < 0.0)
		return (1);
	return (0);
}

t_3d cy_normal(t_cylinder *cylinder, t_3d hitpoint, t_ray *ray)
{
	float h;
	t_3d a;
	t_3d centre;
	t_3d normal;
	t_3d bc = sub_product(hitpoint, cylinder->point);
	h = dot_product(bc, bc);
	h = sqrt(h - sqr(cylinder->rayon));
	centre = add_product(multiply_v(h, cylinder->orient), cylinder->point);
	normal = get_norm(sub_product(hitpoint, centre));
	if (dot_product(ray->endpoint, normal) > 0.f)
		normal = multiply_v(-1.f, normal);
	return (normal);
}

float auto_dot(t_3d a)
{
	return (dot_product(a, a));
}

int inter_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	int ret;
	t_3d oc;
	t_3d dir;
	t_3d ocdir;
	t_3d quadra;
	t_2d t;
	t_3d hitp;
	float discriminant;
	ret = 0;
	oc = sub_product(ray->startpoint, cylinder->point);
	dir = sub_product(ray->endpoint, multiply_v(dot_product(ray->endpoint, cylinder->orient), cylinder->orient));
	ocdir = sub_product(oc, multiply_v(dot_product(oc, cylinder->orient), cylinder->orient));

	quadra.x = dot_product(dir, dir);
	quadra.y = 2 * dot_product(dir, ocdir);
	quadra.z = dot_product(ocdir, ocdir) - sqr(cylinder->rayon);

	discriminant = sqr(quadra.y) - (4.0 * quadra.x * quadra.z);
	if (discriminant < 0.0)
		return (0);

	t.x = (-quadra.y + sqrt(discriminant)) / (2.0 * quadra.x);
	t.y = (-quadra.y - sqrt(discriminant)) / (2.0 * quadra.x);
	hitp = add_product(multiply_v(t.x, ray->endpoint), ray->startpoint);
	if (t.x > 0.0001f && t.x < ray->t && inside_cyl(cylinder, ray, t.x))
	{
		ray->shape_normale = cy_normal(cylinder, hitp, ray);
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		//ray->color = cylinder->color;
		ray->t = t.x;
		ret = 1;
	}
	hitp = add_product(multiply_v(t.y, ray->endpoint), ray->startpoint);
	if (t.y > 0.0001f && t.y < ray->t && inside_cyl(cylinder, ray, t.y))
	{
		ray->shape_normale = cy_normal(cylinder, hitp, ray);
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		//ray->color = cylinder->color;
		ray->t = t.y;
		ret = 1;
	}
	return (ret);
}

int inter_cylinders(t_ray *ray, t_cylinder *cylinder)
{
	int ret;
	ret = 0;
	while (cylinder)
	{
		if (inter_cylinder(ray, cylinder))
			ret = 1;
		cylinder = cylinder->next;
	}
	return (ret);
}