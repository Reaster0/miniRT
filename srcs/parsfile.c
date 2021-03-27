/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:51:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 16:13:48 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <fcntl.h>

int		pars_res(char *str, t_2d *res)
{
	int i;

	i = 0;
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

int		pars_ambient(char *str, int *ambi)
{
	int		i;
	float	intens;
	t_3d	color;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	intens = itof(str, &i);
	fix_float(intens, 0, 1);
	while (str[i] == ' ')
		i++;
	if (!read3d(str, &color, &i))
		return (0);
	fix_3d(&color, 0, 255);
	color = multiply_v(intens, color);
	*ambi = create_trgb(0, color.x, color.y, color.z);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		error_file(t_shapes *shapes, t_2d *res)
{
	if (!shapes->camera)
	{
		printf("Error\nCamera is missing in the file captain!");
		return (0);
	}
	if (!res->x || !res->y)
	{
		printf("Error\nCaptain! did you've forget to add a screen size?");
		return (0);
	}
	return (1);
}

int		check_pars_error(char *path, int *fd)
{
	if ((*fd = open(path, O_RDONLY)) == -1)
	{
		printf("Error\nhey i can't read this ...thing(%s) captain?", path);
		return (0);
	}
	if (!check_name(path))
		return (0);
	return (1);
}

int		parsfile(char *path, t_2d *res, int *ambi, t_shapes *shapes)
{
	char	*str;
	int		fd_re_li[3];

	fd_re_li[1] = 1;
	fd_re_li[2] = 1;
	if (!check_pars_error(path, &fd_re_li[0]))
		return (0);
	while ((fd_re_li[1] = get_next_line(fd_re_li[0], &str)) != -1)
	{
		if (!parsline(str, res, ambi, shapes))
		{
			printf("Error\ncaptain captain! check the line %d\n", fd_re_li[2]);
			end_all_life(shapes);
			fd_re_li[1] = -1;
			break ;
		}
		fd_re_li[2]++;
		free(str);
		if (!fd_re_li[1])
			break ;
	}
	if (fd_re_li[1] == -1)
		return (0);
	close(fd_re_li[0]);
	return (error_file(shapes, res));
}
