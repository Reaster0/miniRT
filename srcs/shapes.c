/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:22:04 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 16:35:47 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d new_3d(float x, float y, float z)
{
	t_3d result;
	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_ray make_ray(t_camera camera, t_2d point)
{
	t_ray result;
	result.startpoint = camera.startpoint;
	result.endpoint = camera.forward;
	result.endpoint = add_product(result.endpoint, multiply_v(point.x * camera.w, camera.right));
	result.endpoint = add_product(result.endpoint, multiply_v(point.y * camera.h, camera.up));
	normalize(&result.endpoint);
	result.t = 1.0e30f;
	result.color = 0x00FFFFFF;

	return (result);
}

t_camera new_camera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio)
{ //pensez a fix le cas ou upguide == target
	t_camera result;
	result.startpoint = origin;
	result.forward = sub_product(target, origin);
	normalize(&result.forward);
	result.right = cross_product(result.forward, upguide);
	normalize(&result.right);
	result.up = cross_product(result.right, result.forward);

	result.h = tan(fov);
	result.w = result.h * ratio;
	return (result);
}

int inter_plane(t_ray *ray, t_plane *plane)
{
	float dDotN;
	float t;
	dDotN = dot_product(ray->endpoint, plane->normal);
	if (dDotN == 0.0f)
		return (0);
	t = dot_product(sub_product(plane->position, ray->startpoint), divide_vr(dDotN, plane->normal));
	if (t <= 0.0001f || t >= ray->t)
		return (0);
	ray->color = plane->color;
	ray->t = t;
	return (1);
}

int inter_sphere(t_ray *ray, t_sphere *sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	float t1;
	float t2;
	t_ray localRay;
	localRay = *ray;
	localRay.startpoint = sub_product(localRay.startpoint, sphere->startpoint);

	a = length2(ray->endpoint);
	b = 2.0 * dot_product(localRay.endpoint, localRay.startpoint);
	c = length2(localRay.startpoint) - sqr(sphere->r);
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
	ray->color = sphere->color;
	return (1);
}

int moller_trumbore(t_3d startpoint, t_3d dirpoint, t_3d *triangle, float *rayt, float *bary_u, float *bary_v)
{
	t_3d edge1;
	t_3d edge2;
	t_3d orig_minus_vert0;
	t_3d cross_raydir_edge2;
	t_3d cross_oriminusvert0_edge1;
	float determinent, inv_determinent;

	edge1 = sub_product(triangle[1], triangle[0]);
	edge2 = sub_product(triangle[2], triangle[0]);

	cross_raydir_edge2 = cross_product(dirpoint, edge2);
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
