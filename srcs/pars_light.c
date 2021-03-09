/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:32:30 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/09 12:31:17 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light *li_last(t_light *light)
{
	if (!(light))
		return (0);
	while (light->next)
		light = light->next;
	return (light);
}

void li_add(t_light **light, t_light *new)
{
	if (!(*light))
	{
		*light = new;
		return;
	}
	li_last(*light)->next = new;
	new->next = 0;
}

t_light *new_li()
{
	t_light *light;
	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->point = new_3d(0, 0, 0);
	light->intens = 0;
	light->next = NULL;
	return (light);
}

int pars_light(char *str, t_light **light)
{
	int i;
	i = 0;
	t_light *li;
	t_3d color;
	if (!str)
		return (0);
	li = new_li();
	li_add(&(*light), li);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &li->point, &i))
		return (0);
	while (str[i] == ' ')
		i++;
	li->intens = itof(str, &i) * 255;
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &color, &i))
		return (0);
	li->color = create_trgb(0, color.x, color.y, color.z);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}