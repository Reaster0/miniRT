/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:12:36 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/15 20:36:10 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H
# include "minirt.h"

t_3d		v_matrix(t_3d point, t_matrix4 matrix);
t_3d		p_matrix(t_3d point, t_matrix4 matrix);
t_matrix4	cam_to_world(t_camera camera);
t_ray		make_ray(t_3d origin, t_3d target, t_3d screen, int ambient);

void		inter_lights(t_ray *ray, t_light *light, t_shapes *shapes);
int			intens_color(t_ray *ray, t_light *light, int color,
			int ray_color, int col_light);

int			inside_cyl(t_cylinder *cylinder, t_ray *ray, float t);
int			inter_cylinders(t_ray *ray, t_cylinder *cylinder);
int			inter_squares(t_ray *ray, t_square *square);
int			inter_triangle2(t_ray *ray, t_triangle *triangle);
int			inter_triangles(t_ray *ray, t_triangle *triangle);
int			inter_plane(t_ray *ray, t_plane *plane);
int			inter_planes(t_ray *ray, t_plane *plane);
int			inter_spheres(t_ray *ray, t_sphere *sphere);

int			intersections(t_ray *ray, t_shapes *shapes, int inter_l);

float		length2(t_3d point);
float		sqr(float number);
float		dot_product(t_3d a, t_3d b);
t_3d		cross_product(t_3d a, t_3d b);
t_3d		sub_product(t_3d a, t_3d b);
t_3d		add_product(t_3d a, t_3d b);
t_3d		multiply_product(t_3d a, t_3d b);
t_ray		calculate(t_ray ray, float t);
void		normalize(t_3d *vector);
void		normalize2d(t_2d *vector);
float		get_normf(float n);
t_3d		add_v(float a, t_3d vector);
t_3d		multiply_v(float a, t_3d vector);
void		sub_v(float a, t_3d *vector);
t_3d		sub_vr(float a, t_3d vector);
t_3d		get_norm(t_3d vector);
void		divide_v(float a, t_3d *vector);
t_3d		divide_vr(float a, t_3d vector);

#endif
