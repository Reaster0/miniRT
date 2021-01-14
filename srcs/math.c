/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:15:31 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/14 18:05:19 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d getnorm2(t_3d vector)
{
	t_3d result;
	result.x = vector.x * vector.x;
	result.y = vector.y * vector.y;
	result.z = vector.z * vector.z;
	return (result);
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
	float norm;
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

float inter_sphere(t_ray ray, t_sphere sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	t_3d vector;
	vector = sub_product(*ray.startpoint, *sphere.startpoint);
	a = dot_product(*ray.startpoint, *ray.startpoint);
	b = 2.0 * dot_product(vector, *ray.dir);
	c = dot_product(vector, vector) - sphere.r * sphere.r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		printf("je touche pas \n");
		return (-1.0);
	}
	return ((-b - sqrt(discriminant)) / (2.0 * a));
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
