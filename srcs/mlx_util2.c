/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:22:21 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 13:23:52 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_val_null(t_2d *res, t_shapes *shapes)
{
	res->x = 0;
	res->y = 0;
	shapes->ambient = 0;
	shapes->camera = NULL;
	shapes->sphere = NULL;
	shapes->cylinder = NULL;
	shapes->light = NULL;
	shapes->plane = NULL;
	shapes->square = NULL;
	shapes->triangle = NULL;
}

int		set_startmlx(t_all *all, t_data **img, t_shapes *shapes, t_2d *res)
{
	all->nbr_img = nbr_cam(shapes->camera);
	all->i = 0;
	all->vars->mlx = mlx_init();
	all->vars->win = mlx_new_window(all->vars->mlx, res->x, res->y,
			"Saint MiniRT");
	*img = malloc(sizeof(t_data) * (all->nbr_img + 1));
	if (!*img)
		return (0);
	all->img_xy = malloc(sizeof(t_2d) * (all->nbr_img + 1));
	if (!all->img_xy)
		return (0);
	all->img = *img;
	return (1);
}

void	fix_screen(t_vars *vars, t_2d *xy)
{
	int x;
	int y;

	mlx_get_screen_size(vars->mlx, &x, &y);
	if (xy->x > x)
		xy->x = x;
	if (xy->y > y)
		xy->y = y;
}

int		end_of_mlx(t_all *all)
{
	int i;

	i = 0;
	while (i <= all->nbr_img)
	{
		mlx_destroy_image(all->vars->mlx, (all->img + i)->img);
		i++;
	}
	free(all->img);
	mlx_destroy_window(all->vars->mlx, all->vars->win);
	mlx_destroy_display(all->vars->mlx);
	free(all->img_xy);
	free(all->vars->mlx);
	exit(0);
	return (1);
}

int		refresh(t_all *all)
{
	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
			(all->img + all->i)->img, 0, 0);
	return (1);
}
