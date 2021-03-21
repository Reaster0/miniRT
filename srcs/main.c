/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/21 18:23:51 by earnaud          ###   ########.fr       */
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

void end_of_mlx(t_all *all)
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
	//mlx_destroy_display(all->vars->mlx);
}

void filter(int id, t_data *img)
{
	t_2d count;

	count.y = 0;
	while (count.y < img->height)
	{
		count.x = 0;
		while (count.x < img->width)
		{
			*(unsigned int *)get_pixel(img, count.x, count.y) = get_opposite(*(unsigned int *)get_pixel(img, count.x, count.y));
			count.x++;
		}
		count.y++;
	}
}

int key_press(int keycode, t_all *all)
{
	if (all->i > all->nbr_img)
		all->i = 0;
	if (all->j > 3)
		all->j = 0;
	if (keycode == 45 || keycode == 110)
	{
		mlx_put_image_to_window(all->vars->mlx, all->vars->win, (all->img + all->i)->img, 0, 0);
		all->i++;
	}
	if (keycode == 53 || keycode == 65307)
		end_of_mlx(all);
	if (keycode == 0)
	{
		filter(all->j++, (all->img + all->i)->img);
		mlx_put_image_to_window(all->vars->mlx, all->vars->win, (all->img + all->i)->img, 0, 0);
	}
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

int main(int argc, char **argv)
{
	t_vars vars;
	t_all all;
	t_data *img;
	t_2d res;
	t_shapes shapes;
	int i = 0;
	int nbr_img;
	if (argc != 2)
	{
		printf("Error\nhey captain i need a file to work with!");
		return (0);
	}
	res.x = 0;
	res.y = 0;
	shapes.ambient = 0;
	shapes.camera = NULL;
	shapes.sphere = NULL;
	shapes.cylinder = NULL;
	shapes.light = NULL;
	shapes.plane = NULL;
	shapes.square = NULL;
	shapes.triangle = NULL;
	if (!(parsfile(argv[1], &res, &shapes.ambient, &shapes)))
		return (0);
	all.nbr_img = nbr_cam(shapes.camera);
	all.i = 1;
	all.j = 0;
	all.vars = &vars;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "Saint MiniRT");
	//vars.data = img;
	img = malloc(sizeof(t_data) * all.nbr_img + 1);
	all.img = img;
	while (i <= all.nbr_img)
	{
		printf("\nimage %d of %d processing\n", i + 1, all.nbr_img + 1);
		img[i] = new_img(&vars, res.y, res.x);
		project(&img[i], res, &shapes, id_cam(shapes.camera, i));
		i++;
	}
	ft_putstr_fd("\nfinished\n", 1);
	end_all_life(&shapes);
	mlx_put_image_to_window(vars.mlx, vars.win, all.img->img, 0, 0);
	key_press(0, &all);
	//mlx_hook(vars.win, 2, 1L << 0, key_test, &vars);
	//mlx_hook(vars.win, 2, 1L << 0, key_press, &all);
	mlx_loop(vars.mlx);
	return (0);
}
