/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:51:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/05 15:34:49 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <fcntl.h>

int pars_res(char *str, t_2d *res)
{
	int i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		res->x = ft_atoi(str + i);
	else
	{
		printf("error camera value\n");
		return (0);
	}
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		res->y = ft_atoi(str + i);
	else
	{
		printf("error camera value\n");
		return (0);
	}
	while (str[i] == ' ')
		i++;
	if (str[i])
	{
		return (0);
		printf("error camera value\n");
	}
}

int pars_cam(char *str, t_shapes *shapes)
{
	static int nbr;
	int ret = 0;
	int i = 0;
	if (nbr == NULL)
		nbr = 0;
	while (str[i] == ' ')
		i++;
}

int parsline(char *str, t_2d *res, t_shapes *shapes)
{
	int i = 0;
	int ret = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == 'R')
			ret = pars_res(str[i + 1], res);
		// pars A
		else if (str[i] == 'c')
			ret = pars_cam(str[i + 1], shapes);
		else if (str[i] == 'l')
			ret = pars_light(str[i + 1], shapes);
		else if (str[i] == 's' && str[i + 1] == 'p')
			ret = pars_sphere(str[i + 2], shapes);
		else if (str[i] == 'p' && str[i + 1] == 'l')
			ret = pars_plane(str[i + 2], shapes);
	}
	return (ret);
}

int parsfile(char *path, t_2d *res, t_shapes *shapes)
{
	char *str;
	int fd;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		printf("error failed to open %s\n", path);
		return (0);
	}
	while (get_next_line(fd, &str) > 0)
		if (!parsline(str, res, shapes))
			printf("error in the line\n");
}