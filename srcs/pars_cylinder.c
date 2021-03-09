/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:19:19 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/09 13:27:24 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_cylinder *cy_last(t_cylinder *cylinder)
{
	if (!(cylinder))
		return (0);
	while (cylinder->next)
		cylinder = cylinder->next;
	return (cylinder);
}

void cy_add(t_cylinder **cylinder, t_cylinder *new)
{
	if (!(*cylinder))
	{
		*cylinder = new;
		return;
	}
	cy_last(*cylinder)->next = new;
	new->next = 0;
}

t_cylinder *new_cy()
{
	t_cylinder *cylinder;
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->color = 0;
	cylinder->next = NULL;
	cylinder->orient = new_3d(0, 0, 0);
	cylinder->height = 0;
	cylinder->point = new_3d(0, 0, 0);
	cylinder->rayon = 0;
	return (cylinder);
}

int pars_cylinder(char *str, t_cylinder **cylinder)
{
	int i = 0;
	t_cylinder *cy;
	t_3d color;
	if (!str)
		return (0);
	cy = new_cy();
	cy_add(&(*cylinder), cy);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &cy->point, &i))
		return (0);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &cy->orient, &i))
		return (0);
	while (str[i] == ' ')
		i++;
	cy->rayon = itof(str, &i);
	while (str[i] == ' ')
		i++;
	cy->height = itof(str, &i);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &color, &i))
		return (0);
	cy->color = create_trgb(0, color.x, color.y, color.z);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}