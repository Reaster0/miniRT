/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:33:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 22:07:55 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_square	*squ_last(t_square *square)
{
	if (!(square))
		return (0);
	while (square->next)
		square = square->next;
	return (square);
}

void		squ_add(t_square **square, t_square *new)
{
	if (!(*square))
	{
		*square = new;
		return ;
	}
	squ_last(*square)->next = new;
	new->next = 0;
}

t_square	*new_squ(void)
{
	t_square *square;

	square = malloc(sizeof(t_square));
	if (!square)
		return (NULL);
	square->color = 0;
	square->next = NULL;
	square->center = new_3d(0, 0, 0);
	square->orient = new_3d(0, 0, 0);
	return (square);
}

int			pars_square2(char *str, t_3d *color, int *i, t_square *squ)
{
	if (str[(*i)] != ' ' && str[(*i)])
		return (0);
	skip(i, str);
	if (!read3d(str, color, i))
		return (0);
	fix_3d(color, 0, 255);
	squ->color = create_trgb(0, color->x, color->y, color->z);
	while (str[(*i)])
	{
		if (str[(*i)] != ' ')
			return (0);
		(*i)++;
	}
	return (1);
}

int			pars_square(char *str, t_square **square)
{
	int			i;
	t_square	*squ;
	t_3d		color;

	i = 0;
	if (!str)
		return (0);
	squ = new_squ();
	squ_add(&(*square), squ);
	skip(&i, str);
	if (!read3d(str, &squ->center, &i))
		return (0);
	squ->center.x *= -1;
	skip(&i, str);
	if (!read3d(str, &squ->orient, &i))
		return (0);
	fix_3d(&squ->orient, -1, 1);
	normalize(&squ->orient);
	skip(&i, str);
	squ->side = itof(str, &i);
	return (pars_square2(str, &color, &i, squ));
}
