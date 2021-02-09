/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:12:36 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/09 16:46:30 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
#define MATH_H
#include "minirt.h"

typedef struct s_matrix4
{
	t_3d c1;
	int c14;
	t_3d c2;
	int c24;
	t_3d c3;
	int c34;
	t_3d c4;
	int c44;
} t_matrix4;


t_ray make_ray(t_camera camera, t_2d point);

void inter_lights(t_ray *ray, t_light **light, t_shapes *shapes);
void inter_light(t_ray *ray, t_light *light, t_shapes *shapes);
int intens_color(t_ray *ray, t_light *light, int color, int ray_color);


int inter_cylinder(t_ray *ray, t_cylinder *cylinder);
int inter_cylinders(t_ray *ray, t_cylinder **cylinder);
int inter_square(t_ray *ray, t_square *square);
int inter_squares(t_ray *ray, t_square **square);
int inter_triangle(t_ray *ray, t_triangle *triangle);
int inter_triangles(t_ray *ray, t_triangle **triangle);
int inter_plane(t_ray *ray, t_plane *plane);
int inter_planes(t_ray *ray, t_plane **plane);
int inter_spheres(t_ray *ray, t_sphere **sphere);
int inter_sphere(t_ray *ray, t_sphere *sphere);
int intersections(t_ray *ray, t_shapes *shapes, int inter_l);


float length2(t_3d point);
float sqr(float number);
float dot_product(t_3d a, t_3d b);
t_3d cross_product(t_3d a, t_3d b);
t_3d sub_product(t_3d a, t_3d b);
t_3d add_product(t_3d a, t_3d b);
t_3d multiply_product(t_3d a, t_3d b);
t_ray calculate(t_ray ray, float t);
void normalize(t_3d *vector);
void normalize2d(t_2d *vector);
float get_normf(float n);
t_3d add_v(float a, t_3d vector);
t_3d multiply_v(float a, t_3d vector);
void sub_v(float a, t_3d *vector);
t_3d sub_vr(float a, t_3d vector);
t_3d get_norm(t_3d vector);
void divide_v(float a, t_3d *vector);
t_3d divide_vr(float a, t_3d vector);

#endif