/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:51:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/09 16:18:01 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <fcntl.h>

int pars_res(char *str, t_2d *res)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		res->x = ft_atoi(str + i);
	else
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		res->y = ft_atoi(str + i);
	else
		return (0);
	return (1);
}

float itof(char *str, int *i)
{
	float result;
	int isneg;
	int flag;
	int j;
	isneg = 0;
	j = 0;
	flag = 0;
	result = 0;
	if (str[*i] == '-')
	{
		isneg = 1;
		(*i)++;
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
		}
		else
		{
			printf("error parsing the value\n");
			return (0);
		}
		(*i)++;
	}
	result *= pow(10, j);
	if (isneg)
		result *= -1;
	return (result);
}

int read3d(char *str, t_3d *value, int *i)
{
	int error;
	error = 1;
	value->x = itof(str, i);
	if (str[*i] == ',')
		(*i)++;
	else
		return (0);
	value->y = itof(str, i);
	if (str[*i] == ',')
		(*i)++;
	else
		return (0);
	value->z = itof(str, i);
	value->w = 0;
	return (1);
}

int pars_ambient(char *str, t_light *ambi)
{
	int i;
	i = 0;
	t_3d color;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	ambi->intens = itof(str, &i) * 255;
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &color, &i))
		return (0);
	ambi->color = create_trgb(0, color.x, color.y, color.z);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int parsline(char *str, t_2d *res, t_light *ambi, t_shapes *shapes)
{
	int ret;
	int i;
	ret = 0;
	i = 0;
	if (*str == 'R' && !res->x && str[1] == ' ')
		ret = pars_res(str + 1, res);
	else if (*str == 'A' && !ambi->color && str[1] == ' ')
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

void end_life(void *p)
{
	free(p);
	p = NULL;
}

void end_all_life(t_shapes *shapes)
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

int parsfile(char *path, t_2d *res, t_light *ambi, t_shapes *shapes)
{
	char *str;
	int fd;
	int ret;
	int line;
	ret = 1;
	line = 1;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		printf("error failed to open %s\n", path);
		return (0);
	}
	while ((ret = get_next_line(fd, &str)) != -1)
	{
		if (!parsline(str, res, ambi, shapes))
		{
			printf("error in the line : %d\n", line);
			end_all_life(shapes);
			ret = -1;
			break;
		}
		line++;
		if (!ret)
			break;
	}
	if (ret == -1)
		return (0);
	close(fd);
	return (1);
}