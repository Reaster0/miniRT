/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:35:52 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 12:33:46 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_sphere		*sphe_last(t_sphere *sphere)
{
	if (!(sphere))
		return (0);
	while (sphere->next)
		sphere = sphere->next;
	return (sphere);
}

void			sphe_add(t_sphere **sphere, t_sphere *new)
{
	if (!(*sphere))
	{
		*sphere = new;
		return ;
	}
	sphe_last(*sphere)->next = new;
	new->next = 0;
}

t_sphere		*new_sphe(void)
{
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->color = 0;
	sphere->next = NULL;
	sphere->r = 0;
	sphere->startpoint = new_3d(0, 0, 0);
	return (sphere);
}

int				pars_sphere2(char *str, t_sphere *sphe, t_3d *color, int *i)
{
	skip(i, str);
	if (!read3d(str, color, i))
		return (0);
	fix_3d(color, 0, 255);
	sphe->color = create_trgb(0, color->x, color->y, color->z);
	sphe->startpoint.x *= -1;
	while (str[(*i)])
	{
		if (str[(*i)] != ' ')
			return (0);
		(*i)++;
	}
	return (1);
}

int				pars_sphere(char *str, t_sphere **sphere)
{
	int			i;
	t_sphere	*sphe;
	t_3d		color;

	i = 0;
	if (!str)
		return (0);
	sphe = new_sphe();
	sphe_add(&(*sphere), sphe);
	skip(&i, str);
	if (!read3d(str, &sphe->startpoint, &i))
		return (0);
	skip(&i, str);
	sphe->r = itof(str, &i);
	if (str[i] != ' ' && str[i])
		return (0);
	if (str[i] != ' ' && str[i])
		return (0);
	return (pars_sphere2(str, sphe, &color, &i));
}
