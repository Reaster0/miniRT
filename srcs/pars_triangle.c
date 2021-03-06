/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:23:04 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 12:39:02 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_triangle		*tri_last(t_triangle *triangle)
{
	if (!(triangle))
		return (0);
	while (triangle->next)
		triangle = triangle->next;
	return (triangle);
}

void			tri_add(t_triangle **triangle, t_triangle *new)
{
	if (!(*triangle))
	{
		*triangle = new;
		return ;
	}
	tri_last(*triangle)->next = new;
	new->next = 0;
}

t_triangle		*new_tri(void)
{
	t_triangle *triangle;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		return (NULL);
	triangle->color = 0;
	triangle->next = NULL;
	triangle->a = new_3d(0, 0, 0);
	triangle->b = new_3d(0, 0, 0);
	triangle->c = new_3d(0, 0, 0);
	return (triangle);
}

int				pars_triangle2(char *str, t_triangle *tri, t_3d *color, int *i)
{
	skip(i, str);
	if (!read3d(str, color, i))
		return (0);
	fix_3d(color, 0, 255);
	tri->color = create_trgb(0, color->x, color->y, color->z);
	tri->a.x *= -1;
	tri->b.x *= -1;
	tri->c.x *= -1;
	while (str[(*i)])
	{
		if (str[(*i)] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int				pars_triangle(char *str, t_triangle **triangle)
{
	int			i;
	t_triangle	*tri;
	t_3d		color;

	i = 0;
	if (!str)
		return (0);
	tri = new_tri();
	tri_add(&(*triangle), tri);
	skip(&i, str);
	if (!read3d(str, &tri->a, &i))
		return (0);
	skip(&i, str);
	if (!read3d(str, &tri->b, &i))
		return (0);
	skip(&i, str);
	if (!read3d(str, &tri->c, &i))
		return (0);
	return (pars_triangle2(str, tri, &color, &i));
}
