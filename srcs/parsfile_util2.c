/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:37:46 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 15:40:27 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		parsline(char *str, t_2d *res, int *ambi, t_shapes *shapes)
{
	int ret;

	ret = 0;
	if (*str == 'R' && !res->x && str[1] == ' ')
		ret = pars_res(str + 1, res);
	else if (*str == 'A' && !*ambi && str[1] == ' ')
		ret = pars_ambient(str + 1, ambi);
	else if (*str == 'c' && str[1] == ' ')
		ret = pars_cam(str + 1, &shapes->camera);
	else if (*str == 'l' && str[1] == ' ')
		ret = pars_light(str + 1, &shapes->light);
	else if (*str == 's' && str[1] == 'p')
		ret = pars_sphere(str + 2, &shapes->sphere);
	else if (*str == 'p' && str[1] == 'l')
		ret = pars_plane(str + 2, &shapes->plane);
	else if (*str == 's' && str[1] == 'q')
		ret = pars_square(str + 2, &shapes->square);
	else if (*str == 'c' && str[1] == 'y')
		ret = pars_cylinder(str + 2, &shapes->cylinder);
	else if (*str == 't' && str[1] == 'r')
		ret = pars_triangle(str + 2, &shapes->triangle);
	else if (!*str)
		ret = 1;
	return (ret);
}

void	end_life(void *p)
{
	free(p);
	p = NULL;
}

void	end_all_life2(t_shapes *shapes, void *p)
{
	while (shapes->plane)
	{
		p = (void *)shapes->plane->next;
		end_life((void *)shapes->plane);
		shapes->plane = (t_plane *)p;
	}
	while (shapes->sphere)
	{
		p = (void *)shapes->sphere->next;
		end_life((void *)shapes->sphere);
		shapes->sphere = (t_sphere *)p;
	}
	while (shapes->square)
	{
		p = (void *)shapes->square->next;
		end_life((void *)shapes->square);
		shapes->square = (t_square *)p;
	}
	while (shapes->triangle)
	{
		p = (void *)shapes->triangle->next;
		end_life((void *)shapes->triangle);
		shapes->triangle = (t_triangle *)p;
	}
}

void	end_all_life(t_shapes *shapes)
{
	void *p;

	while (shapes->camera)
	{
		p = (void *)shapes->camera->next;
		end_life((void *)shapes->camera);
		shapes->camera = (t_camera *)p;
	}
	while (shapes->cylinder)
	{
		p = (void *)shapes->cylinder->next;
		end_life((void *)shapes->cylinder);
		shapes->cylinder = (t_cylinder *)p;
	}
	while (shapes->light)
	{
		p = (void *)shapes->light->next;
		end_life((void *)shapes->light);
		shapes->light = (t_light *)p;
	}
	end_all_life2(shapes, p);
}
