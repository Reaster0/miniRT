/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:22:04 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/02 15:06:06 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d new_3d(float x, float y, float z)
{
	t_3d result;
	result.x = -x;
	result.y = y;
	result.z = z;
	return (result);
}

t_2d new_2d(float x, float y)
{
	t_2d result;
	result.x = x;
	result.y = y;
	return (result);
}

t_cylinder *new_cylinder(t_3d point, t_3d orient, t_2d h_r, int color)
{
	t_cylinder *cylinder;
	cylinder = malloc(sizeof(t_cylinder));
	cylinder->point = point;
	cylinder->orient = orient;
	cylinder->rayon = h_r.y;
	cylinder->height = h_r.x;
	cylinder->pointup = add_product(cylinder->point, multiply_v(cylinder->height, cylinder->orient));

	cylinder->color = color;
	return (cylinder);
}

t_sphere *new_sphere(t_3d startpoint, float r, int color)
{
	t_sphere *sphere;
	sphere = malloc(sizeof(t_sphere));
	sphere->startpoint = startpoint;
	sphere->r = r;
	sphere->color = color;
	return (sphere);
}

t_plane *new_plane(t_3d position, t_3d normal, int color)
{
	t_plane *plane;
	plane = malloc(sizeof(t_plane));
	plane->position = position;
	plane->normal = normal;
	plane->color = color;
	return (plane);
}

t_triangle *new_triangle(t_3d a, t_3d b, t_3d c, int color)
{
	t_triangle *triangle;
	triangle = malloc(sizeof(t_triangle));
	triangle->a = a;
	triangle->b = b;
	triangle->c = c;
	triangle->color = color;
	return (triangle);
}

t_square *new_square(t_3d a, t_3d b, t_3d c, t_3d d, int color)
{
	t_square *square;
	square = malloc(sizeof(t_square));
	square->a = a;
	square->b = b;
	square->c = c;
	square->d = d;
	square->color = color;
	return (square);
}