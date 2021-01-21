/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:22:04 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 17:51:05 by earnaud          ###   ########.fr       */
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

t_sphere *new_sphere(t_3d startpoint, float r, int color)
{
	t_sphere *sphere;
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->startpoint = startpoint;
	sphere->r = r;
	sphere->color = color;
	return (sphere);
}

t_plane *new_plane(t_3d position, t_3d normal, int color)
{
	t_plane *plane;
	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->position = position;
	plane->normal = normal;
	plane->color = color;
	return (plane);
}