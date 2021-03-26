/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:14:52 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 22:23:53 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_camera	*cam_last(t_camera *camera)
{
	if (!(camera))
		return (0);
	while (camera->next)
		camera = camera->next;
	return (camera);
}

void		cam_add(t_camera **camera, t_camera *new)
{
	if (!(*camera))
	{
		*camera = new;
		return ;
	}
	cam_last(*camera)->next = new;
	new->next = 0;
}

t_camera	*new_cam(void)
{
	t_camera *camera;

	camera = malloc(sizeof(t_camera));
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

int			pars_cam2(char *str, t_camera *cam, int *i)
{
	normalize(&cam->forward);
	skip(i, str);
	cam->fov = fix_float(itof(str, i) / 2 * M_PI / 180.f, 0, 180);
	cam->startpoint.x *= -1;
	cam->forward.x *= -1;
	while (str[(*i)])
	{
		if (str[(*i)] != ' ')
			return (0);
		(*i)++;
	}
	return (1);
}

int			pars_cam(char *str, t_camera **camera)
{
	int			i;
	t_camera	*cam;

	i = 0;
	if (!str)
		return (0);
	cam = new_cam();
	cam_add(&(*camera), cam);
	skip(&i, str);
	if (!read3d(str, &cam->startpoint, &i))
		return (0);
	skip(&i, str);
	if (!read3d(str, &cam->forward, &i))
		return (0);
	fix_3d(&cam->forward, -1, 1);
	return (pars_cam2(str, cam, &i));
}
