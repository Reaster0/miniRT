/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:35:21 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 14:26:26 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	color_up(int *trgb1, int trgb2)
{
	if (get_r(*trgb1) < get_r(trgb2))
		change_r(trgb1, get_r(trgb2));
	if (get_g(*trgb1) < get_g(trgb2))
		change_g(trgb1, get_g(trgb2));
	if (get_b(*trgb1) < get_b(trgb2))
		change_b(trgb1, get_b(trgb2));
}

void	change_r(int *trgb, int r)
{
	*trgb = create_trgb(get_t(*trgb), r, get_g(*trgb), get_b(*trgb));
}

void	change_g(int *trgb, int g)
{
	*trgb = create_trgb(get_t(*trgb), get_r(*trgb), g, get_b(*trgb));
}

void	change_b(int *trgb, int b)
{
	*trgb = create_trgb(get_t(*trgb), get_r(*trgb), get_g(*trgb), b);
}
