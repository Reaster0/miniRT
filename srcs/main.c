/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 13:30:50 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			key_press(int keycode, t_all *all)
{
	if (keycode == 45 || keycode == 110)
	{
		all->i++;
		if (all->i > all->nbr_img)
			all->i = 0;
		mlx_put_image_to_window(all->vars->mlx, all->vars->win,
				(all->img + all->i)->img, 0, 0);
		printf("img %d\n", all->i);
	}
	if (keycode == 53 || keycode == 65307)
		end_of_mlx(all);
	if (keycode == 113)
		filter_invert(all->vars, all->img + all->i, all->img_xy);
	if (keycode == 119)
		filter_psyche(all->vars, all->img + all->i, all->img_xy);
	return (1);
}

int			nbr_cam(t_camera *camera)
{
	int i;

	i = 0;
	while (camera->next)
	{
		camera = camera->next;
		i++;
	}
	return (i);
}

t_camera	*id_cam(t_camera *camera, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		camera = camera->next;
		j++;
	}
	return (camera);
}

static int	check_error_main(int argc)
{
	if (argc < 2)
	{
		printf("Error\nhey captain i need a file to work with!");
		return (0);
	}
	if (argc > 3)
	{
		printf("Error\ncaptain i think there is too much arguments hehe...");
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_vars		vars;
	t_all		all;
	t_data		*img;
	t_shapes	shapes;

	if (!check_error_main(argc))
		return (0);
	set_val_null(&all.res, &shapes);
	if (!(parsfile(argv[1], &all.res, &shapes.ambient, &shapes)))
		return (0);
	all.vars = &vars;
	if (argc == 3)
	{
		if (!check_error(argv[2]))
			return (0);
		return (export_bmp(&shapes, &all, img));
	}
	if (!set_startmlx(&all, &img, &shapes, &all.res))
		return (0);
	fix_screen(&vars, &all.res);
	process_fullinter(&vars, img, &all, &shapes);
	mlx_put_image_to_window(vars.mlx, vars.win, all.img->img, 0, 0);
	mlx_run(&vars, &all);
	return (1);
}
