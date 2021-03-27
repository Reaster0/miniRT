/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:35:18 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 15:38:33 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	skip(int *i, char *str)
{
	while (str[(*i)] == ' ')
		(*i)++;
}

void	fix_3d(t_3d *d3, float min, float max)
{
	d3->w = fix_float(d3->w, min, max);
	d3->x = fix_float(d3->x, min, max);
	d3->y = fix_float(d3->y, min, max);
	d3->z = fix_float(d3->z, min, max);
}

float	fix_float(float nbr, float min, float max)
{
	if (nbr > max)
		return (max);
	if (nbr < min)
		return (min);
	return (nbr);
}

int		read3d(char *str, t_3d *value, int *i)
{
	int error;

	error = 1;
	value->x = itof(str, i);
	if (str[*i] == ',')
		(*i)++;
	else
		return (0);
	value->y = itof(str, i);
	if (str[*i] == ',')
		(*i)++;
	else
		return (0);
	value->z = itof(str, i);
	value->w = 0;
	return (1);
}
