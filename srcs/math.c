/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:15:31 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/22 12:52:38 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	b = 2.f * dot_product(localRay.endpoint, localRay.startpoint);
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

int inter_planes(t_ray *ray, t_plane **plane)
{
	int i = 0;
	int ret;
	ret = 0;
	while (plane[i])
	{
		if (inter_plane(ray, plane[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int inter_spheres(t_ray *ray, t_sphere **sphere)
{
	int i = 0;
	int ret;
	ret = 0;
	while (sphere[i])
	{
		if (inter_sphere(ray, sphere[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int inter_triangles(t_ray *ray, t_triangle **triangle)
{
	int i = 0;
	int ret;
	ret = 0;
	while (triangle[i])
	{
		if (inter_triangle(ray, triangle[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

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

	if (determinent > -0.000001 && determinent < 0.000001)
		return (0);
	inv_determinent = 1.0 / determinent;

	orig_minus_vert0 = sub_product(ray->startpoint, triangle->a);

	triangle->barycentric.y = dot_product(orig_minus_vert0, cross_raydir_edge2) * inv_determinent;
	if (triangle->barycentric.y < 0.0 || triangle->barycentric.y > 1.0)
		return (0);

	cross_oriminusvert0_edge1 = cross_product(orig_minus_vert0, edge1);

	triangle->barycentric.z = dot_product(ray->endpoint, cross_oriminusvert0_edge1) * inv_determinent;
	if (triangle->barycentric.z < 0.0 || triangle->barycentric.z > 1.0)
		return (0);
	triangle->barycentric.x = 1 - triangle->barycentric.y - triangle->barycentric.z;

	t = dot_product(edge2, cross_oriminusvert0_edge1) * inv_determinent;
	if (t < ray->t)
	{
		ray->t = t;
		ray->color = triangle->color;
	}
	return (1);
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
	float norm;
	norm = sqrt(sqr(vector->x) + sqr(vector->y) + sqr(vector->z));
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

t_3d divide_vr(float a, t_3d vector)
{
	vector.x /= a;
	vector.y /= a;
	vector.z /= a;
	return (vector);
}

void sub_v(float a, t_3d *vector)
{
	vector->x -= a;
	vector->y -= a;
	vector->z -= a;
}

t_3d add_v(float a, t_3d vector)
{
	vector.x += a;
	vector.y += a;
	vector.z += a;
	return (vector);
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
	temp = ray;
	temp.endpoint = multiply_v(t, ray.endpoint);
	return (temp);
}