/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:56:24 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/17 17:23:41 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int inside_cyl(t_cylinder *cylinder, t_ray *ray, float t)
{
	t_3d hitpoint;
	t_3d bottom;
	t_3d top;
	return (1);
	cylinder->pointup = add_product(cylinder->point, multiply_v(cylinder->height, cylinder->orient));
	hitpoint = add_product(ray->startpoint, multiply_v(t, ray->endpoint));
	bottom = sub_product(hitpoint, cylinder->point);
	top = sub_product(hitpoint, cylinder->pointup);

	if (dot_product(cylinder->orient, bottom) > 0 && dot_product(cylinder->orient, top) < 0)
		return (1);
	return (0);
}

int inter_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	int ret;
	t_3d center;
	t_3d oc;
	t_3d dir;
	t_3d ocdir;
	t_3d quadra;
	t_2d t;
	t_2d temp;
	t_3d temp3d;
	t_3d hitp;
	float discriminant;
	ret = 0;
	oc = sub_product(ray->startpoint, cylinder->point);
	dir = sub_product(ray->endpoint, multiply_v(dot_product(ray->endpoint, cylinder->orient), cylinder->orient));
	ocdir = sub_product(oc, multiply_v(dot_product(oc, cylinder->orient), cylinder->orient));

	quadra.x = dot_product(dir, dir);
	quadra.y = 2 * dot_product(dir, ocdir);
	quadra.z = dot_product(ocdir, ocdir) - sqr(cylinder->rayon);

	discriminant = sqr(quadra.y) - (4.f * quadra.x * quadra.z);
	if (discriminant < 0)
		return (0);

	t.x = (-quadra.x + sqrt(discriminant)) / (2 * quadra.x);
	t.y = (-quadra.y - sqrt(discriminant)) / (2 * quadra.x);
	hitp = add_product(multiply_v(t.x, ray->endpoint), ray->startpoint);
	if (t.x > 0.0001f && t.x < ray->t && inside_cyl(cylinder, ray, t.x))
	{
		ray->t = t.x;
		temp.x = dot_product(sub_product(hitp, cylinder->point), cylinder->orient);
		temp3d = add_product(cylinder->point, multiply_v(temp.x, cylinder->orient));
		ray->shape_normale = get_norm(sub_product(hitp, temp3d));
		//ray->shape_normale = sub_product(hitp, add_product(cylinder->point, multiply_v(dot_product(sub_product(hitp, cylinder->point), cylinder->orient), cylinder->orient)));
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		ret = 1;
	}
	hitp = add_product(multiply_v(t.x, ray->endpoint), ray->startpoint);
	if (t.y > 0.0001f && t.y < ray->t && inside_cyl(cylinder, ray, t.y))
	{
		ray->t = t.y;
		temp.x = dot_product(sub_product(hitp, cylinder->point), cylinder->orient);
		temp3d = add_product(cylinder->point, multiply_v(temp.x, cylinder->orient));
		ray->shape_normale = get_norm(sub_product(hitp, temp3d));
		//ray->shape_normale = sub_product(hitp, add_product(cylinder->point, multiply_v(dot_product(sub_product(hitp, cylinder->point), cylinder->orient), cylinder->orient)));
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		ret = 1;
	}
	// quadra.x = dot_product(dir, dir);
	// quadra.y = 2.0 * dot_product(dir, ocdir);
	// quadra.z = dot_product(ocdir, ocdir) - sqr(cylinder->rayon);

	// discriminant = sqr(quadra.y) - (4.0 * quadra.x * quadra.z);
	// if (discriminant < 0.0)
	// 	return (0);

	// t.x = (-quadra.y + sqrt(discriminant)) / (2.0 * quadra.x);
	// t.y = (-quadra.y - sqrt(discriminant)) / (2.0 * quadra.x);

	// if (t.x > 0.000001 && inside_cyl(cylinder, ray, t.x) && t.x < ray->t)
	// {
	// 	ray->t = t.x;
	// 	ray->shape_point = cylinder->point;
	// 	ray->shape_color = cylinder->color;
	// 	ret = 1;
	// }
	// if (t.y > 0.000001 && inside_cyl(cylinder, ray, t.y) && t.y < ray->t)
	// {
	// 	ray->t = t.y;
	// 	ray->shape_point = cylinder->point;
	// 	ray->shape_color = cylinder->color;
	// 	ret = 1;
	// }
	// if (ret)
	// {
	// 	t_3d hit_p = add_product(ray->startpoint, multiply_v(ray->t, ray->endpoint));
	// 	//cas ou je touche les caps
	// 	t_3d inter_vec = sub_product(cylinder->pointup, hit_p);
	// 	// if (!dot_product(inter_vec, cylinder->orient))
	// 	// 	ray->shape_normale = cylinder->orient;

	// 	// inter_vec = sub_product(cylinder->point, hit_p);
	// 	// if (!dot_product(inter_vec, cylinder->orient))
	// 	// 	ray->shape_normale = cylinder->orient;

	// 	t_3d cylinder_center = divide_vr(2, add_product(cylinder->point, cylinder->pointup));
	// 	t_3d cyloritocenter = sub_product(cylinder_center, hit_p);

	// 	inter_vec = multiply_v(dot_product(cyloritocenter, cylinder->orient), cylinder->orient);
	// 	t_3d pcylaxis = add_product(cylinder_center, inter_vec);
	// 	ray->shape_normale = get_norm(sub_product(hit_p, pcylaxis));
	// }
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