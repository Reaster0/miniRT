/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:20:34 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/10 16:24:01 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"

float dot_product(t_3d a, t_3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_3d cross_product(t_3d a, t_3d b)
{
	t_3d ret;
	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

t_3d sub_product(t_3d a, t_3d b)
{
	t_3d ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

int moller_trumbore(t_3d startpoint, t_3d endpoint, t_3d *triangle, float *rayt, float *bary_u, float *bary_v)
{
	t_3d edge1;
	t_3d edge2;
	t_3d orig_minus_vert0;
	t_3d cross_raydir_edge2;
	t_3d cross_oriminusvert0_edge1;
	float determinent, inv_determinent;

	edge1 = sub_product(triangle[1], triangle[0]);
	edge2 = sub_product(triangle[2], triangle[0]);

	cross_raydir_edge2 = cross_product(endpoint, edge2);
	determinent = dot_product(edge1, cross_raydir_edge2);

	//je sais pas pourquoi ni comment ça marche
	if (determinent > -0.000001 && determinent < 0.000001)
		return (0);
	inv_determinent = 1.0 / determinent;

	orig_minus_vert0 = sub_product(startpoint, triangle[0]);

	//calcul pour voir si l'on est dans le triangle barycentrique
	*bary_u = dot_product(orig_minus_vert0, cross_raydir_edge2) * inv_determinent;
	if (*bary_u < 0.0 || *bary_u > 1.0)
		return 0;

	cross_oriminusvert0_edge1 = cross_product(orig_minus_vert0, edge1);

	*bary_v = dot_product(cross_oriminusvert0_edge1, orig_minus_vert0) * inv_determinent;
	if (*bary_v < 0.0 || *bary_u > 1.0)
		return (0);
	// calcul de la longueur de notre rayon
	*rayt = dot_product(edge2, cross_oriminusvert0_edge1) * inv_determinent;
	return (1);
}
