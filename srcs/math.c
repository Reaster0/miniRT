/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:15:31 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 17:30:00 by earnaud          ###   ########.fr       */
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