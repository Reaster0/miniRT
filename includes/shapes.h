/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:23:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/24 12:08:45 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
#define SHAPES_H
#include "minirt.h"


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

typedef struct s_ray
{
	t_3d startpoint;
	t_3d endpoint;
	float t;
	int color;
} t_ray;

typedef struct s_camera
{
	t_3d startpoint;
	t_3d forward;
	t_3d up;
	t_3d right;
	float h;
	float w;
} t_camera;

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

typedef struct s_triangle
{
	t_3d a;
	t_3d b;
	t_3d c;
	t_3d barycentric;
	int color;
} t_triangle;

typedef struct s_square
{
	t_3d a;
	t_3d b;
	t_3d c;
	t_3d d;
	int color;
} t_square;

t_camera new_camera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio);
t_3d new_3d(float x, float y, float z);
t_sphere *new_sphere(t_3d startpoint, float r, int color);
t_plane *new_plane(t_3d position, t_3d normal, int color);
t_triangle *new_triangle(t_3d a, t_3d b, t_3d c, int color);
t_square *new_square(t_3d a, t_3d b, t_3d c, t_3d d, int color);


#endif