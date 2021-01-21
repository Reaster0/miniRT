/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:12:36 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 14:44:41 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
#define MATH_H
#include "minirt.h"
#include "shapes.h"

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
#endif