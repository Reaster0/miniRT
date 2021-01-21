/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:23:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 14:44:30 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
#define SHAPES_H
#include "minirt.h"
#include "math.h"

typedef struct s_3d
{
	float x;
	float y;
	float z;
} t_3d;

typedef struct s_2d
{
	float y;
	float x;
} t_2d;

typedef struct s_plane
{	
	t_3d position;
	t_3d normal;
	int color;
} t_plane;

typedef struct s_sphere
{
	t_3d startpoint;
	float r;
	int color;
} t_sphere;

int moller_trumbore(t_3d startpoint, t_3d endpoint, t_3d *triangle, float *rayt, float *bary_u, float *bary_v);
int inter_plane(t_ray *ray, t_plane *plane);
int inter_sphere(t_ray *ray, t_sphere *sphere);

#endif