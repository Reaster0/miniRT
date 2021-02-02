/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:35:21 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/02 15:27:54 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int get_b(int trgb)
{
	return (trgb & 0xFF);
}

int get_opposite(int color)
{
	return (0xFFFFFF - color);
}

int add_shade(double shade, int color)
{
	return (color * shade);
}