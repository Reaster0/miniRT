/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:22:18 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/12 16:15:25 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_plane *pla_last(t_plane *plane)
{
	if (!(plane))
		return (0);
	while (plane->next)
		plane = plane->next;
	return (plane);
}

void pla_add(t_plane **plane, t_plane *new)
{
	if (!(*plane))
	{
		*plane = new;
		return;
	}
	pla_last(*plane)->next = new;
	new->next = 0;
}

t_plane *new_pla()
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

int pars_plane(char *str, t_plane **plane)
{
	int i = 0;
	t_plane *pla;
	t_3d color;
	if (!str)
		return (0);
	pla = new_pla();
	pla_add(&(*plane), pla);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &pla->position, &i))
		return (0);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &pla->normal, &i))
		return (0);
	fix_3d(&pla->normal, -1, 1);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &color, &i))
		return (0);
	fix_3d(&color, 0, 255);
	pla->color = create_trgb(0, color.x, color.y, color.z);
	pla->position.x *= -1;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}