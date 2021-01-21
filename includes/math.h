/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:12:36 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 17:32:26 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
#define MATH_H
#include "minirt.h"


t_camera new_camera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio);
t_ray make_ray(t_camera camera, t_2d point);

int moller_trumbore(t_3d startpoint, t_3d endpoint, t_3d *triangle, float *rayt, float *bary_u, float *bary_v);
int inter_plane(t_ray *ray, t_plane *plane);
int inter_sphere(t_ray *ray, t_sphere *sphere);
int intersections(t_ray *ray, t_plane **plane, t_sphere **sphere);


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
t_3d add_v(float a, t_3d vector);
t_3d multiply_v(float a, t_3d vector);
void sub_v(float a, t_3d *vector);
void divide_v(float a, t_3d *vector);
t_3d divide_vr(float a, t_3d vector);

#endif