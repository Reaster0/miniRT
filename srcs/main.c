/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 15:53:27 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//normaliser toutes les orientation dans le parsing

int intens_color(t_ray *ray, t_light *light, int color, int ray_color, int col_light)
{
	float temp;
	int result;

	temp = (((float)color / 255) * (col_light * dot_product(get_norm(sub_product(light->point, light->hit.shape_point)), light->hit.shape_normale) / length2(sub_product(light->point, light->hit.endpoint))));

	result = temp * 255;

	if (result > 255)
		result = 255;
	if (result < ray_color)
		result = ray_color;
	return (result);
}

int intersections(t_ray *ray, t_shapes *shapes, int inter_l)
{
	int ret;
	ret = 0;

	if (inter_cylinders(ray, shapes->cylinder))
		ret = 1;
	if (inter_spheres(ray, shapes->sphere))
		ret = 1;
	if (inter_planes(ray, shapes->plane))
		ret = 1;
	if (inter_triangles(ray, shapes->triangle))
		ret = 1;
	if (inter_squares(ray, shapes->square))
		ret = 1;

	if (ret == 1 && inter_l)
		inter_lights(ray, shapes->light, shapes);

	return (ret);
}

void project(t_data *data, t_2d res, t_shapes *shapes, t_camera *camera)
{
	float i;
	t_2d count;
	t_3d screen_coord;
	t_ray ray;

	count.y = 0;
	while (count.y < res.y)
	{
		count.x = 0;
		while (count.x < res.x)
		{
			screen_coord.x = 2 * ((count.x + 0.5) / res.x) - 1.f;
			screen_coord.y = 1 - 2 * ((count.y + 0.5) / res.y);
			screen_coord.x *= tan(camera->fov);
			screen_coord.y *= tan(camera->fov);
			screen_coord.x *= res.x / res.y;
			screen_coord.z = -1.f;
			printf("\rLoading (%.0f%%)", (count.y / res.y) * 100);
			ray = make_ray(camera->startpoint, camera->forward, screen_coord, shapes->ambient);
			if (intersections(&ray, shapes, 1))
				mlx_pixel_put_fast(data, count.x, count.y, ray.color);
			count.x++;
		}
		count.y++;
	}
}

int key_test(int keycode, t_vars *vars)
{
	printf("\nthe keycode is %d\n", keycode);
	return (1);
}

int end_of_mlx(t_all *all)
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

int refresh(t_all *all)
{
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, (all->img + all->i)->img, 0, 0);
	return (1);
}

int key_press(int keycode, t_all *all)
{
	if (keycode == 45 || keycode == 110)
	{
		all->i++;
		if (all->i > all->nbr_img)
			all->i = 0;
		mlx_put_image_to_window(all->vars->mlx, all->vars->win, (all->img + all->i)->img, 0, 0);
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

int nbr_cam(t_camera *camera)
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

t_camera *id_cam(t_camera *camera, int i)
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

void set_val_null(t_2d *res, t_shapes *shapes, int *i)
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
	i = 0;
}

int set_startmlx(t_all *all, t_data **img, t_shapes *shapes, t_2d *res)
{
	all->nbr_img = nbr_cam(shapes->camera);
	all->i = 0;
	all->vars->mlx = mlx_init();
	all->vars->win = mlx_new_window(all->vars->mlx, res->x, res->y, "Saint MiniRT");
	*img = malloc(sizeof(t_data) * (all->nbr_img + 1));
	if (!*img)
		return (0);
	all->img_xy = malloc(sizeof(t_2d) * (all->nbr_img + 1));
	if (!all->img_xy)
		return (0);
	all->img = *img;
	return (1);
}

void process_fullinter(t_vars *vars, t_data *img, t_all *all, t_shapes *shapes)
{
	int i;
	i = 0;
	while (i <= all->nbr_img)
	{
		printf("\nimage %d of %d processing\n", i + 1, all->nbr_img + 1);
		img[i] = new_img(vars, all->res.y, all->res.x);
		(all->img_xy + i)->x = img[i].width;
		(all->img_xy + i)->y = img[i].height;
		project(img + i, all->res, shapes, id_cam(shapes->camera, i));
		i++;
	}
	ft_putstr_fd("\nfinished\n", 1);
	end_all_life(shapes);
}

void fix_screen(t_vars *vars, t_2d *xy)
{
	int x;
	int y;
	mlx_get_screen_size(vars->mlx, &x, &y);
	if (xy->x > x)
		xy->x = x;
	if (xy->y > y)
		xy->y = y;
}

int main(int argc, char **argv)
{
	t_vars vars;
	t_all all;
	t_data *img;
	t_shapes shapes;

	if (argc < 2)
	{
		printf("Error\nhey captain i need a file to work with!");
		return (0);
	}
	if (argc > 3)
	{
		printf("Error\nhuu captain i think there is too much arguments hehe...");
		return (0);
	}
	set_val_null(&all.res, &shapes, &all.j);
	if (!(parsfile(argv[1], &all.res, &shapes.ambient, &shapes)))
		return (0);
	all.vars = &vars;
	if (argc == 3)
	{
		if (!check_error(argv[2]))
			return (0);
		return (export_bmp(&shapes, &all, img, &vars));
	}
	if (!set_startmlx(&all, &img, &shapes, &all.res))
		return (0);
	fix_screen(&vars, &all.res);
	process_fullinter(&vars, img, &all, &shapes);
	mlx_put_image_to_window(vars.mlx, vars.win, all.img->img, 0, 0);
	//key_press(53, &all);
	//mlx_hook(vars.win, 2, 1L << 0, key_test, &vars);
	mlx_hook(vars.win, 15, 1L << 16, refresh, &all);
	mlx_hook(vars.win, 33, 1L << 17, end_of_mlx, &all);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &all);
	mlx_loop(vars.mlx);
	return (1);
}
