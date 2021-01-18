/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:15:31 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/18 17:17:38 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float sqr(float number)
{
	return (number * number);
}

float length2(t_3d point)
{
	return (sqr(point.x) + sqr(point.y) + sqr(point.z));
}

void normalize2d(t_2d *vector)
{
	float norm;
	norm = sqrt(vector->x * vector->x + vector->y * vector->y);
	vector->x /= norm;
	vector->y /= norm;
}

void normalize(t_3d *vector)
{
	//check du cas zero
	float norm;
	if (!vector->x && !vector->y && !vector->z)
		return ();
	norm = sqrt(vector->x * vector->x + vector->y + vector->y + vector->z * vector->z);
	vector->x /= norm;
	vector->y /= norm;
	vector->z /= norm;
}

t_3d multiply_v(float a, t_3d vector)
{
	vector.x *= a;
	vector.y *= a;
	vector.z *= a;
	return (vector);
}

void divide_v(float a, t_3d *vector)
{
	vector->x /= a;
	vector->y /= a;
	vector->z /= a;
}

void sub_v(float a, t_3d *vector)
{
	vector->x -= a;
	vector->y -= a;
	vector->z -= a;
}

void add_v(float a, t_3d *vector)
{
	vector->x += a;
	vector->y += a;
	vector->z += a;
}

t_3d multiply_product(t_3d a, t_3d b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

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

t_3d add_product(t_3d a, t_3d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_3d sub_product(t_3d a, t_3d b)
{
	t_3d ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_ray calculate(t_ray ray, float t)
{
	t_ray temp;
	t_3d temp2 = multiply_v(t, ray.endpoint);
	temp = ray;
	temp.endpoint = temp2;
	return (temp);
}

int inter_sphere(t_ray *ray, t_sphere sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	float t1;
	float t2;
	t_ray localRay;
	localRay = *ray;
	localRay.startpoint = sub_product(localRay.startpoint, sphere.startpoint);

	a = length2(ray->endpoint);
	b = 2.0 * dot_product(localRay.endpoint, localRay.startpoint);
	c = length2(localRay.startpoint) - sqr(sphere.r);
	discriminant = sqr(b) - 4 * a * c;
	//printf("discriminant =%f\na =%f\nb =%f\nc =%f\n", discriminant, a, b, c);
	if (discriminant < 0.0f)
		return (0);

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 > 0.0001f && t1 < 1.0e30f)
		ray->t = t1;
	else if (t2 > 0.0001f && t2 < 1.0e30f)
		ray->t = t2;
	else
	{
		return (0);
	}
	printf("ptn on a trouve une intersection\n");
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
