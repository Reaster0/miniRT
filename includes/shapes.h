/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:23:57 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/09 17:10:11 by earnaud          ###   ########.fr       */
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
	float fov;
	void *next;
} t_camera;

typedef struct s_plane
{	
	t_3d position;
	t_3d normal;
	int color;
	void *next;
} t_plane;

typedef struct s_sphere
{
	t_3d startpoint;
	float r;
	int color;
	void *next;
} t_sphere;

typedef struct s_triangle
{
	t_3d a;
	t_3d b;
	t_3d c;
	t_3d barycentric;
	int color;
	void *next;
} t_triangle;

typedef struct s_square
{
	t_3d center;
	t_3d orient;
	float side;
	int color;
	void *next;
} t_square;

typedef struct s_cylinder
{
	t_3d point;
	t_3d pointup;
	t_3d orient;
	float rayon;
	float height;
	int color;
	void *next;
} t_cylinder;
 
typedef struct s_light
{
	t_3d point;	
	t_3d normale;
	float r;
	float intens;
	int color;
	t_ray hit;
	void *next;
} t_light;

typedef struct s_shapes
{
	t_camera *camera;
	t_light *light;
	t_plane *plane;
	t_sphere *sphere;
	t_triangle *triangle;
	t_square *square;
	t_cylinder *cylinder;
} t_shapes;

typedef struct s_matrix4
{
	t_3d r1;
	t_3d r2;
	t_3d r3;
	t_3d r4;
} t_matrix4;

t_3d new_3d(float x, float y, float z);
t_2d new_2d(float x, float y);


#endif