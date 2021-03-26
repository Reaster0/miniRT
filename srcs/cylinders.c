/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:56:24 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 14:44:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			inside_cyl(t_cylinder *cylinder, t_ray *ray, float t)
{
	t_3d	hitpoint;
	t_3d	bottom;
	t_3d	top;

	cylinder->pointup = add_product(cylinder->point,
			multiply_v(cylinder->height, cylinder->orient));
	hitpoint = add_product(ray->startpoint, multiply_v(t, ray->endpoint));
	bottom = sub_product(hitpoint, cylinder->point);
	top = sub_product(hitpoint, cylinder->pointup);
	if (dot_product(cylinder->orient, bottom) > 0.0 &&
			dot_product(cylinder->orient, top) < 0.0)
		return (1);
	return (0);
}

int			cy_assign(t_cylinder *cylinder, t_3d hitpoint, t_ray *ray, int t)
{
	float	h;
	t_3d	centre;
	t_3d	bc;

	bc = sub_product(hitpoint, cylinder->point);
	h = sqrt(dot_product(bc, bc) - sqr(cylinder->rayon));
	centre = add_product(multiply_v(h, cylinder->orient), cylinder->point);
	ray->shape_normale = get_norm(sub_product(hitpoint, centre));
	if (dot_product(ray->endpoint, ray->shape_normale) > 0.f)
		ray->shape_normale = multiply_v(-1.f, ray->shape_normale);
	ray->shape_point = cylinder->point;
	ray->shape_color = cylinder->color;
	ray->t = t;
	return (1);
}

static int	solutions(t_ray *ray, t_cylinder *cylinder, t_2d *t)
{
	t_3d	oc;
	t_3d	dir;
	t_3d	ocdir;
	t_3d	quadra;
	float	discriminant;

	oc = sub_product(ray->startpoint, cylinder->point);
	dir = sub_product(ray->endpoint, multiply_v(dot_product(ray->endpoint,
					cylinder->orient), cylinder->orient));
	ocdir = sub_product(oc, multiply_v(dot_product(oc, cylinder->orient),
				cylinder->orient));
	quadra.x = dot_product(dir, dir);
	quadra.y = 2 * dot_product(dir, ocdir);
	quadra.z = dot_product(ocdir, ocdir) - sqr(cylinder->rayon);
	discriminant = sqr(quadra.y) - (4.0 * quadra.x * quadra.z);
	if (discriminant < 0.0)
		return (0);
	t->x = (-quadra.y + sqrt(discriminant)) / (2.0 * quadra.x);
	t->y = (-quadra.y - sqrt(discriminant)) / (2.0 * quadra.x);
	return (1);
}

int			inter_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	int		ret;
	t_2d	t;
	t_3d	hitp;

	ret = 0;
	if (!solutions(ray, cylinder, &t))
		return (0);
	hitp = add_product(multiply_v(t.x, ray->endpoint), ray->startpoint);
	if (t.x > 0.000001f && t.x < ray->t && inside_cyl(cylinder, ray, t.x))
		ret = cy_assign(cylinder, hitp, ray, t.x);
	hitp = add_product(multiply_v(t.y, ray->endpoint), ray->startpoint);
	if (t.y > 0.000001f && t.y < ray->t && inside_cyl(cylinder, ray, t.y))
		ret = cy_assign(cylinder, hitp, ray, t.y);
	return (ret);
}

int			inter_cylinders(t_ray *ray, t_cylinder *cylinder)
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
