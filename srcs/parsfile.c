/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:51:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/05 17:08:06 by earnaud          ###   ########.fr       */
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
		printf("error res value\n");
		return (0);
	}
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		res->y = ft_atoi(str + i);
	else
	{
		printf("error res value\n");
		return (0);
	}
	while (str[i] == ' ')
		i++;
	if (str[i])
	{
		return (0);
		printf("error res value\n");
	}
}

double itof(char *str, int *i)
{
	double result;
	int isneg;
	int flag;
	int j;
	isneg = 0;
	j = 0;
	flag = 0;
	if (str[*i] == '-')
	{
		isneg = 1;
		*i++;
	}
	while (str[*i] && (ft_isdigit(str[*i]) || str[*i] == '.'))
	{
		if (ft_isdigit(str[*i]))
		{
			result = (result * 10) + str[*i] - '0';
			if (flag)
				j--;
		}
		else if (str[*i] == '.')
		{
			if (flag)
				return (0);
			flag = 1;
			*i++;
		}
		*i++;
	}
	result *= pow(10, j);
	if (isneg)
		result * -1;
	return (result);
}

int read3d(char *str, t_3d *value)
{
	int i;
	i = 0;
	value->x = itof(str, &i);
	if (str[i] == ',')
		i++;
	else
		return (0);
	value->y = itof(str, &i);
	if (str[i] == ',')
		i++;
	else
		return (0);
	value->z = itof(str, &i);
	return (1);
}

int pars_cam(char *str, t_shapes *shapes)
{
	int ret = 1;
	int i = 0;
	t_camera *camera;
	camera = shapes->camera;
	while (camera->next)
		camera = camera->next;
	if (!read3d(str + i, &camera->startpoint))
		ret = 0;
	while (str[i] == ' ')
		i++;
	if (!read3d(str + i, &camera->forward))
		ret = 0;
	while (str[i] == ' ')
		i++;
	camera->fov = itof(str, &i);
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