/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:51:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/07 16:28:42 by earnaud          ###   ########.fr       */
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
		else
		{
			printf("error parsing the value\n");
			return (0);
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

int pars_cam(char *str, t_camera *camera)
{
	int ret = 1;
	int i = 0;
	t_camera *cam;

	if (!(cam = malloc(sizeof(t_camera))))
		return (0);
	while (camera->next)
		camera = camera->next;
	camera->next = &cam;
	if (!read3d(str + i, &cam->startpoint))
		ret = 0;
	while (str[i] == ' ')
		i++;
	if (!read3d(str + i, &cam->forward))
		ret = 0;
	while (str[i] == ' ')
		i++;
	camera->fov = itof(str, &i) / 2 * M_PI / 180.f;
	return (ret);
}

int pars_light(char *str, t_light *light)
{
	int ret = 1;
	int i = 0;
	t_light *li;
	t_3d color;
	if (!(li = malloc(sizeof(t_light))))
		return (0);
	while (light->next)
		light = light->next;
	light->next = li;
	li->intens = itof(str, &i) * 255;
	while (str[i] == ' ')
		i++;
	if (!read3d(str + i, &color))
		ret = 0;
	li->color = create_trgb(0, color.x, color.y, color.z);
	return (ret);
}

int pars_ambient(char *str, t_light *ambi)
{
	int ret = 1;
	int i = 0;
	t_3d color;
	if (!(ambi = malloc(sizeof(t_light))))
		return (0);
	while (str[i] == ' ')
		i++;
	ambi->intens = itof(str, &i) * 255;
	while (str[i] == ' ')
		i++;
	if (!read3d(str + i, &color))
		ret = 0;
	ambi->color = create_trgb(0, color.x, color.y, color.z);
	return (ret);
}

int pars_sphere(char *str, t_sphere *sphere)
{
	int ret = 1;
	int i = 0;
	t_sphere *sphe;
	t_3d color;
	if (!(sphe = malloc(sizeof(t_sphere))))
		return (0);
	while (sphere->next)
		sphere = sphere->next;
	sphere->next = sphe;
	while (str[i] == ' ')
		i++;
	if (!read3d(str + i, &sphe->startpoint))
		ret = 0;
	while (str[i] == ' ')
		i++;
	sphe->r = itof(str, &i) * 255;
	while (str[i] == ' ')
		i++;
	if (!read3d(str + i, &color_up))
		ret = 0;
	sphe->color = create_trgb(0, color.x, color.y, color.z);
	return (ret);
}

int parsline(char *str, t_2d *res, t_light *ambi, t_shapes *shapes)
{
	int i = 0;
	int ret = 0;
	int r = 0;
	int a = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == 'R' && !r)
		{
			ret = pars_res(str[i + 1], res);
			r = 1;
		}
		else if (str[i] == 'A' && !a)
		{
			ret = pars_ambi(str[i + 1], ambi);
			a = 1;
		}
		else if (str[i] == 'c')
			ret = pars_cam(str[i + 1], shapes->camera);
		else if (str[i] == 'l')
			ret = pars_light(str[i + 1], shapes);
		else if (str[i] == 's' && str[i + 1] == 'p')
			ret = pars_sphere(str[i + 2], shapes);
		else if (str[i] == 'p' && str[i + 1] == 'l')
			ret = pars_plane(str[i + 2], shapes);
		else if (str[i] == '\n')
		{
			i++;
			ret = 1;
		}
	}
	return (ret);
}

int parsfile(char *path, t_2d *res, t_shapes *shapes)
{
	char *str;
	int fd;
	int ret;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		printf("error failed to open %s\n", path);
		return (0);
	}
	while ((ret = get_next_line(fd, &str)) > 0)
		if (!parsline(str, res, shapes))
			printf("error in the line\n");
	if (ret == -1)
	{
		printf("error reading the file\n");
		return (0);
	}
	return (1);
}