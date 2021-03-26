/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:32:30 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 22:41:54 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light		*li_last(t_light *light)
{
	if (!(light))
		return (0);
	while (light->next)
		light = light->next;
	return (light);
}

void		li_add(t_light **light, t_light *new)
{
	if (!(*light))
	{
		*light = new;
		return ;
	}
	li_last(*light)->next = new;
	new->next = 0;
}

t_light		*new_li(void)
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

int			pars_light2(char *str, t_light *li, t_3d *color, int *i)
{
	if (str[(*i)] != ' ' && str[(*i)])
		return (0);
	skip(i, str);
	if (!read3d(str, color, i))
		return (0);
	fix_3d(color, 0, 255);
	li->color = create_trgb(0, color->x, color->y, color->z);
	li->point.x *= -1;
	while (str[(*i)])
	{
		if (str[(*i)] != ' ')
			return (0);
		(*i)++;
	}
	return (1);
}

int			pars_light(char *str, t_light **light)
{
	int		i;
	t_light	*li;
	t_3d	color;

	i = 0;
	if (!str)
		return (0);
	li = new_li();
	li_add(&(*light), li);
	skip(&i, str);
	if (!read3d(str, &li->point, &i))
		return (0);
	skip(&i, str);
	li->intens = fix_float(itof(str, &i) * 255, 0, 255);
	return (pars_light2(str, li, &color, &i));
}
