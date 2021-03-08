/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:51:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/08 17:20:25 by earnaud          ###   ########.fr       */
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
	{
		printf("error res value\n");
		return (0);
	}
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		res->y = ft_atoi(str + i);
	else
	{
		printf("error res value\n");
		return (0);
	}
	return (1);
	// while (ft_isdigit(str[i]))
	// i++;
	// while (str[i] == ' ')
	// 	i++;
	// if (str[i])
	// {
	// 	printf("error res value\n");
	// 	return (0);
	// }
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

t_camera *cam_last(t_camera *camera)
{
	if (!(camera))
		return (0);
	while (camera->next)
		camera = camera->next;
	return (camera);
}

void cam_add(t_camera *camera, t_camera *new)
{
	if (!(camera))
	{
		camera = new;
		return;
	}
	cam_last(camera)->next = new;
	new->next = 0;
}

t_camera *new_cam()
{
	t_camera *camera;
	camera = malloc(sizeof(t_camera *));
	if (!camera)
		return (NULL);
	camera->fov = 0;
	camera->forward = new_3d(0, 0, 0);
	camera->next = NULL;
	camera->right = new_3d(0, 0, 0);
	camera->startpoint = new_3d(0, 0, 0);
	camera->up = new_3d(0, 0, 0);
	return (camera);
}

int pars_cam(char *str, t_camera *camera)
{
	int ret = 1;
	int i = 0;
	t_camera *cam;
	if (!str)
		return (0);
	cam = new_cam();
	cam_add(camera, cam);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &cam->startpoint, &i))
		return (0);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &cam->forward, &i))
		return (0);
	while (str[i] == ' ')
		i++;
	cam->fov = itof(str, &i) / 2 * M_PI / 180.f;
	return (1);
}

int pars_light(char *str, t_light **light)
{
	// int ret = 1;
	// int i = 0;
	// t_light *li;
	// t_3d color;
	// if (!(li = malloc(sizeof(t_light *))))
	// 	return (0);
	// while (light->next)
	// 	light = light->next;
	// light->next = li;
	// li->intens = itof(str, &i) * 255;
	// while (str[i] == ' ')
	// 	i++;
	// if (!read3d(str, &color, &i))
	// 	ret = 0;
	// li->color = create_trgb(0, color.x, color.y, color.z);
	// return (ret);
}

int pars_ambient(char *str, t_light *ambi)
{
	int ret = 1;
	int i = 0;
	t_3d color;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	ambi->intens = itof(str, &i) * 255;
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &color, &i))
		ret = 0;
	ambi->color = create_trgb(0, color.x, color.y, color.z);
	return (ret);
}

int pars_sphere(char *str, t_sphere **sphere)
{
	// int ret = 1;
	// int i = 0;
	// t_sphere *sphe;
	// t_3d color;
	// if (!str)
	// 	return (0);
	// if (!(sphe = malloc(sizeof(t_sphere *))))
	// 	return (0);
	// while (sphere->next)
	// 	sphere = sphere->next;
	// sphere->next = sphe;
	// while (str[i] == ' ')
	// 	i++;
	// if (!read3d(str, &sphe->startpoint, &i))
	// 	ret = 0;
	// while (str[i] == ' ')
	// 	i++;
	// sphe->r = itof(str, &i) * 255;
	// while (str[i] == ' ')
	// 	i++;
	// if (!read3d(str, &color, &i))
	// 	ret = 0;
	// sphe->color = create_trgb(0, color.x, color.y, color.z);
	// return (ret);
}

int pars_plane(char *str, t_plane **plane)
{
	// int ret = 1;
	// int i = 0;
	// t_plane *pla;
	// t_3d color;
	// if (!str)
	// 	return (0);
	// if (!(pla = malloc(sizeof(t_plane *))))
	// 	return (0);
	// while (plane->next)
	// 	plane = plane->next;
	// plane->next = pla;
	// while (str[i] == ' ')
	// 	i++;
	// if (!read3d(str, &pla->position, &i))
	// 	ret = 0;
	// while (str[i] == ' ')
	// 	i++;
	// if (!read3d(str, &pla->normal, &i))
	// 	ret = 0;
	// while (str[i] == ' ')
	// 	i++;
	// if (!read3d(str, &color, &i))
	// 	ret = 0;
	// pla->color = create_trgb(0, color.x, color.y, color.z);
	// return (ret);
}

int parsline(char *str, t_2d *res, t_light *ambi, t_shapes *shapes)
{
	int ret = 0;
	int r = 0;
	int a = 0;
	if (*str == 'R' && !r)
	{
		ret = pars_res(str + 1, res);
		r = 1;
	}
	else if (*str == 'A' && !a)
	{
		ret = pars_ambient(str + 1, ambi);
		a = 1;
	}
	else if (*str == 'c')
		ret = pars_cam(str + 1, shapes->camera);
	else if (*str == 'l')
		ret = pars_light(str + 1, shapes->light);
	else if (*str == 's' && str[1] == 'p')
		ret = pars_sphere(str + 2, shapes->sphere);
	else if (*str == 'p' && str[1] == 'l')
		ret = pars_plane(str + 2, shapes->plane);
	else if (!*str)
		ret = 1;
	return (ret);
}

int parsfile(char *path, t_2d *res, t_light *ambi, t_shapes *shapes)
{
	char *str;
	int fd;
	int ret;
	ret = 1;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		printf("error failed to open %s\n", path);
		return (0);
	}
	while ((ret = get_next_line(fd, &str)) != -1)
	{
		if (!parsline(str, res, ambi, shapes))
		{
			printf("error in the line\n");
			ret = -1;
			break;
		}
		if (!ret)
			break;
	}
	if (ret == -1)
		return (0);
	close(fd);
	return (1);
}