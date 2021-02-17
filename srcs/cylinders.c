/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:56:24 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/17 20:56:48 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int inside_cyl(t_cylinder *cylinder, t_ray *ray, float t)
{
	t_3d hitpoint;
	t_3d bottom;
	t_3d top;

	hitpoint = add_product(ray->startpoint, multiply_v(t, ray->endpoint));
	bottom = sub_product(hitpoint, cylinder->point);
	top = sub_product(hitpoint, cylinder->pointup);

	if (dot_product(cylinder->orient, bottom) > 0.0 && dot_product(cylinder->orient, top) < 0.0)
		return (1);
	return (0);
}

int inter_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	int ret;
	t_3d oc;
	t_3d dir;
	t_3d ocdir;
	t_3d quadra;
	t_2d t;
	float discriminant;
	ret = 0;

	oc = sub_product(ray->startpoint, cylinder->point);
	dir = sub_product(ray->endpoint, multiply_v(dot_product(ray->endpoint, cylinder->orient), cylinder->orient));
	ocdir = sub_product(oc, multiply_v(dot_product(oc, cylinder->orient), cylinder->orient));

	quadra.x = dot_product(dir, dir);
	quadra.y = 2.0 * dot_product(dir, ocdir);
	quadra.z = dot_product(ocdir, ocdir) - sqr(cylinder->rayon);

	discriminant = sqr(quadra.y) - (4.0 * quadra.x * quadra.z);
	if (discriminant < 0.0)
		return (0);

	t.x = (-quadra.y + sqrt(discriminant)) / (2.0 * quadra.x);
	t.y = (-quadra.y - sqrt(discriminant)) / (2.0 * quadra.x);

	if (t.x > 0.000001 && inside_cyl(cylinder, ray, t.x) && t.x < ray->t)
	{
		ray->t = t.x;
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		ret = 1;
	}
	if (t.y > 0.000001 && inside_cyl(cylinder, ray, t.y) && t.y < ray->t)
	{
		ray->t = t.y;
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		ret = 1;
	}
	if (ret)
	{
		t_3d hit_p = add_product(ray->startpoint, multiply_v(ray->t, ray->endpoint));
		//cas ou je touche les caps
		t_3d inter_vec = sub_product(cylinder->pointup, hit_p);
		// if (!dot_product(inter_vec, cylinder->orient))
		// 	ray->shape_normale = cylinder->orient;

		// inter_vec = sub_product(cylinder->point, hit_p);
		// if (!dot_product(inter_vec, cylinder->orient))
		// 	ray->shape_normale = cylinder->orient;

		t_3d cylinder_center = divide_vr(2, add_product(cylinder->point, cylinder->pointup));
		t_3d cyloritocenter = sub_product(cylinder_center, hit_p);

		inter_vec = multiply_v(dot_product(cyloritocenter, cylinder->orient), cylinder->orient);
		t_3d pcylaxis = add_product(cylinder_center, inter_vec);
		ray->shape_normale = get_norm(sub_product(hit_p, pcylaxis));
	}

	// if (length2(sub_product(multiply_v(ray->t, ray->endpoint), cylinder->pointup)) < cylinder->rayon)
	// 	ray->shape_normale = cylinder->orient;
	// if (length2(sub_product(multiply_v(ray->t, ray->endpoint), cylinder->point)) < cylinder->rayon)
	// 	ray->shape_normale = multiply_v(-1.f, cylinder->orient);
	// else
	// {
	// 	int t2 = dot_product(sub_product(multiply_v(ray->t, ray->endpoint), cylinder->point), cylinder->orient);
	// 	t_3d pt = add_product(cylinder->point, multiply_v(t2, cylinder->orient));
	// 	ray->shape_normale = get_norm(sub_product(multiply_v(ray->t, ray->endpoint), pt));
	// }
	return (ret);
}

int inter_cylinders(t_ray *ray, t_cylinder **cylinder)
{
	int i = 0;
	int ret;
	ret = 0;
	while (cylinder[i])
	{
		if (inter_cylinder(ray, cylinder[i]))
			ret = 1;
		i++;
	}
	return (ret);
}