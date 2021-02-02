/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:12:36 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/01 11:50:33 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
#define MATH_H
#include "minirt.h"



t_ray make_ray(t_camera camera, t_2d point);

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
int intersections(t_ray *ray, t_plane **plane, t_sphere **sphere, t_triangle **triangle, t_square **square, t_cylinder ** cylinder);


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
t_3d get_norm(t_3d vector);
void divide_v(float a, t_3d *vector);
t_3d divide_vr(float a, t_3d vector);

#endif