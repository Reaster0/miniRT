/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:19:26 by earnaud           #+#    #+#             */
/*   Updated: 2020/12/22 19:12:43 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "mlx.h"

typedef struct s_3d
{
	double x;
	double y;
	double z;
} t_3d;

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
void mlx_pixel_put_fast(t_data *data, int x, int y, int color);
void pixel_square(t_data *data, int x, int y, int sx, int sy, int color);
#endif