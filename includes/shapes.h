/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:23:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/28 16:30:48 by earnaud          ###   ########.fr       */
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
	float r;
	float intens;
	t_ray hit;
	t_ray normale;
} t_light;

t_camera new_camera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio);
t_3d new_3d(float x, float y, float z);
t_2d new_2d(float x, float y);
t_cylinder *new_cylinder(t_3d point, t_3d orient, t_2d h_r, int color);
t_sphere *new_sphere(t_3d startpoint, float r, int color);
t_plane *new_plane(t_3d position, t_3d normal, int color);
t_triangle *new_triangle(t_3d a, t_3d b, t_3d c, int color);
t_square *new_square(t_3d a, t_3d b, t_3d c, t_3d d, int color);


#endif