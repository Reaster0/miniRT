/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:19:26 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/14 17:02:04 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "../dependencies/libft/libft.h"
#include "../includes/math.h"

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
	t_3d *startpoint;
	t_3d *dir;
	t_3d *forward;
	t_3d *up;
	t_3d *right;
	float h;
	float w;
} t_ray;

typedef struct s_sphere
{
	t_3d *startpoint;
	float r;
} t_sphere;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int height;
	int width;
} t_data;

typedef struct s_vars
{
	void *mlx;
	void *win;
	t_data *data;
} t_vars;

int create_trgb(int t, int r, int g, int b);
int get_t(int trgb);
int get_r(int trgb);
int get_g(int trgb);
int get_b(int trgb);
int get_opposite(int color);
int add_shade(double shade, int color);
t_data new_img(t_vars *vars, int y, int x);
void img_adress(t_data *data);
int next_frame(t_vars *vars);
void mlx_pixel_put_fast(t_data *data, int x, int y, int color);
void pixel_square(t_data *data, int y, int x, int sx, int sy, int color);

float dot_product(t_3d a, t_3d b);
t_3d cross_product(t_3d a, t_3d b);
t_3d sub_product(t_3d a, t_3d b);
t_3d add_product(t_3d a, t_3d b);
int moller_trumbore(t_3d startpoint, t_3d endpoint, t_3d *triangle, float *rayt, float *bary_u, float *bary_v);
void normalize(t_3d *vector);
void normalize2d(t_2d *vector);
t_3d add_v(float a, t_3d vector);
t_3d multiply_v(float a, t_3d vector);
t_3d sub_v(float a, t_3d vector);
t_3d divide_v(float a, t_3d vector);

#endif