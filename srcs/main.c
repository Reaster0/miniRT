/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/17 16:13:55 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//normaliser toutes les orientation dans le parsing

int intens_color(t_ray *ray, t_light *light, int color, int ray_color, int col_light)
{
	float temp;
	int result;
	//rajouter la couleur de la lumiere
	// temp = (((float)color / 255) * (light->intens * dot_product(get_norm(sub_product(light->point, light->hit.shape_point)), light->hit.shape_normale) / length2(sub_product(light->point, light->hit.endpoint))));

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

	if (inter_spheres(ray, shapes->sphere))
		ret = 1;
	if (inter_planes(ray, shapes->plane))
		ret = 1;
	if (inter_triangles(ray, shapes->triangle))
		ret = 1;
	if (inter_squares(ray, shapes->square))
		ret = 1;
	if (inter_cylinders(ray, shapes->cylinder))
		ret = 1;
	if (ret == 1 && inter_l)
		inter_lights(ray, shapes->light, shapes);

	return (ret);
}

void project(t_data *data, t_2d res, t_shapes *shapes, int ambient)
{
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
			screen_coord.x *= tan(shapes->camera->fov);
			screen_coord.y *= tan(shapes->camera->fov);
			screen_coord.x *= res.x / res.y;

			screen_coord.z = -1.f;

			ray = make_ray(shapes->camera->startpoint, shapes->camera->forward, screen_coord, ambient);
			if (intersections(&ray, shapes, 1))
				mlx_pixel_put_fast(data, count.x, count.y, ray.color);
			count.x++;
		}
		count.y++;
	}
}

// IMPORTANT RAJOUTER LE STARTPOINT DU RAY A TOUT LES CALCULS DE HITPOINTS

int main(int argc, char **argv)
{
	t_vars vars;
	t_data img;
	t_2d res;
	t_shapes shapes;
	int ambient;
	//check if the file is a .rt
	if (argc != 2)
	{
		printf("error with the argument\n");
		return (0);
	}
	res.x = 0;
	res.y = 0;
	ambient = 0;
	shapes.camera = NULL;
	shapes.sphere = NULL;
	shapes.cylinder = NULL;
	shapes.light = NULL;
	shapes.plane = NULL;
	shapes.square = NULL;
	shapes.triangle = NULL;

	if (!(parsfile(argv[1], &res, &ambient, &shapes)))
		printf("error reading the file\n");
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "MiniRT");
	img = new_img(&vars, res.y, res.x);

	project(&img, res, &shapes, ambient);
	ft_putstr_fd("finished\n", 1);
	end_all_life(&shapes);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
