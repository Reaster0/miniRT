/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:22:18 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 12:26:06 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_plane		*pla_last(t_plane *plane)
{
	if (!(plane))
		return (0);
	while (plane->next)
		plane = plane->next;
	return (plane);
}

void		pla_add(t_plane **plane, t_plane *new)
{
	if (!(*plane))
	{
		*plane = new;
		return ;
	}
	pla_last(*plane)->next = new;
	new->next = 0;
}

t_plane		*new_pla(void)
{
	t_plane *plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->color = 0;
	plane->next = NULL;
	plane->normal = new_3d(0, 0, 0);
	plane->position = new_3d(0, 0, 0);
	return (plane);
}

int			pars_plane2(char *str, t_plane *pla, t_3d *color, int *i)
{
	skip(i, str);
	if (!read3d(str, color, i))
		return (0);
	fix_3d(color, 0, 255);
	pla->color = create_trgb(0, color->x, color->y, color->z);
	pla->position.x *= -1;
	while (str[(*i)])
	{
		if (str[(*i)] != ' ')
			return (0);
		(*i)++;
	}
	return (1);
}

int			pars_plane(char *str, t_plane **plane)
{
	int		i;
	t_plane	*pla;
	t_3d	color;

	i = 0;
	if (!str)
		return (0);
	pla = new_pla();
	pla_add(&(*plane), pla);
	skip(&i, str);
	if (!read3d(str, &pla->position, &i))
		return (0);
	skip(&i, str);
	if (!read3d(str, &pla->normal, &i))
		return (0);
	fix_3d(&pla->normal, -1, 1);
	normalize(&pla->normal);
	return (pars_plane2(str, pla, &color, &i));
}
