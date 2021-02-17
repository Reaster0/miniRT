/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:23:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/17 11:22:52 by earnaud          ###   ########.fr       */
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
	float w;
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
	t_3d shape_point;
	t_3d shape_normale;
	int shape_color;
	float t;
	int color;
} t_ray;

typedef struct s_camera
{
	t_3d startpoint;
	t_3d forward;
	t_3d up;
	t_3d right;
	t_3d zero;
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

typedef struct s_cylinder
{
	t_3d point;
	t_3d pointup;
	t_3d orient;
	float rayon;
	float height;
	int color;
} t_cylinder;
 
typedef struct s_light
{
	t_3d point;	
	t_3d normale;
	float r;
	float intens;
	int color;
	t_ray hit;
} t_light;

typedef struct s_shapes
{
	t_plane **plane;
	t_sphere **sphere;
	t_triangle **triangle;
	t_square **square;
	t_cylinder **cylinder;
} t_shapes;

typedef struct s_matrix4
{
	t_3d r1;
	t_3d r2;
	t_3d r3;
	t_3d r4;
} t_matrix4;

t_camera new_camera(t_3d origin, t_3d target);
t_3d new_3d(float x, float y, float z);
t_2d new_2d(float x, float y);
t_cylinder *new_cylinder(t_3d point, t_3d orient, t_2d h_r, int color);
t_sphere *new_sphere(t_3d startpoint, float r, int color);
t_plane *new_plane(t_3d position, t_3d normal, int color);
t_triangle *new_triangle(t_3d a, t_3d b, t_3d c, int color);
t_square *new_square(t_3d a, t_3d b, t_3d c, t_3d d, int color);
t_light *new_light(t_3d point, int intens);


#endif