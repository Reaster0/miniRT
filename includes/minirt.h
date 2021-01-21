/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:19:26 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 14:33:06 by earnaud          ###   ########.fr       */
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
#include "shapes.h"
#include "math.h"

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

#endif