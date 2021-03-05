/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/05 15:39:39 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int intens_color(t_ray *ray, t_light *light, int color, int ray_color)
{
	float temp;
	int result;
	//rajouter la couleur de la lumiere
	temp = (((float)color / 255) * (light->intens * dot_product(get_norm(sub_product(light->point, light->hit.shape_point)), light->hit.shape_normale) / length2(sub_product(light->point, light->hit.endpoint))));

	//un soucis sur la correction gamma
	//temp /= pow(1.f, 2.2);

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
	t_light **light;

	light = malloc(sizeof(t_light *) * 4);
	//light[0] = new_light(new_3d(0.f, 0.f, 0.f), 80);
	light[1] = new_light(new_3d(9.f, 12, -2), 10);
	light[0] = new_light(new_3d(10.f, 3.f, -2.f), 150);
	light[1] = NULL;
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
	//faire le calcul de lumiere ici

	if (ret == 1 && inter_l)
		inter_lights(ray, light, shapes);

	return (ret);
}

void project(t_data *data, t_2d resolution, int color)
{
	t_2d count;
	// float ratio;
	// float fov;
	// t_shapes shapes;

	// shapes.sphere = malloc(sizeof(t_sphere *) * 6);
	// shapes.sphere[0] = new_sphere(new_3d(1.0f, 0.0f, 13.0f), 4.f, 0x900C3F);
	// shapes.sphere[1] = new_sphere(new_3d(4.f, 2.f, 5.f), 4.f, 0x59e1a7);
	// shapes.sphere[2] = new_sphere(new_3d(-40.f, -1.5f, 6.f), 4.f, 0xFF00FF);
	// shapes.sphere[3] = new_sphere(new_3d(-5.f, 2.f, 13.f), 3.f, 0x00FFFF);
	// shapes.sphere[1] = NULL;

	// shapes.plane = malloc(sizeof(t_plane *) * 7);
	// shapes.plane[1] = new_plane(new_3d(0.f, -5.f, 0.f), new_3d(0.f, 1.f, 0.f), 0xFFFFFF);
	// shapes.plane[0] = new_plane(new_3d(0.f, 0.f, 34.f), new_3d(0.f, 0.0f, 1.f), create_trgb(0, 255, 255, 255));
	// shapes.plane[2] = new_plane(new_3d(0.f, 20.f, 0.f), new_3d(0.f, -1.f, 0.f), 0xFF5733);
	// shapes.plane[4] = new_plane(new_3d(30.f, 0.f, 0.f), new_3d(-1.f, 0.f, 0.f), 0xFF0000);
	// shapes.plane[3] = new_plane(new_3d(-30.f, 0.f, 0.f), new_3d(1.f, 0.f, 0.f), 0xFF0000);
	// shapes.plane[5] = new_plane(new_3d(0.f, 0.f, -30), new_3d(0.f, 0.f, 1), 0xFFFFFF);
	// shapes.plane[6] = NULL;

	// //triangle backwards need a fix
	// shapes.triangle = malloc(sizeof(t_triangle *) * 3);
	// shapes.triangle[1] = new_triangle(new_3d(-4.f, -1.f, -6.f), new_3d(-1.f, -1.f, 6.f), new_3d(-4.f, 4.f, 6.f), 0x420420);
	// shapes.triangle[0] = new_triangle(new_3d(0.f, 2.f, -5.f), new_3d(4.f, 2.f, 4.f), new_3d(1.5f, 5.f, 4.f), 0x420420);
	// shapes.triangle[0] = NULL;

	// shapes.square = malloc(sizeof(t_square) * 2);
	// shapes.square[0] = new_square(new_3d(4.f, 1.f, 5.f), new_3d(8.f, 1.f, 5.f), new_3d(8.f, 5.f, 7.f), new_3d(4.f, 5.f, 7.f), create_trgb(0, 66, 4, 32));
	// shapes.square[0] = NULL;

	// shapes.cylinder = malloc(sizeof(t_cylinder *) * 2);
	// shapes.cylinder[0] = new_cylinder(new_3d(2.f, 0.f, 6.f), new_3d(0.f, 1.f, 0.5f), new_2d(4, 2), 0x420dab);
	// shapes.cylinder[0] = NULL;

	fov = 90.f / 2 * M_PI / 180.f;
	ratio = resolution.x / resolution.y;
	t_3d screen_coord;
	t_ray ray;
	t_3d origin = new_3d(0.f, 0.f, 0.f);
	t_3d target = new_3d(0.f, 0.f, 1.f);

	count.y = 0;
	while (count.y < resolution.y)
	{
		count.x = 0;
		while (count.x < resolution.x)
		{
			// screen_coord.x = (2.0f * count.x) / resolution.x - 1.0f;
			// screen_coord.y = (-2.0f * count.y) / resolution.y + 1.0f;

			screen_coord.x = 2 * ((count.x + 0.5) / resolution.x) - 1.f;
			screen_coord.y = 1 - 2 * ((count.y + 0.5) / resolution.y);
			screen_coord.x *= tan(fov);
			screen_coord.y *= tan(fov);
			screen_coord.x *= ratio;

			screen_coord.z = -1.f;

			//printf("compare x=%f & y=%f with oldx=%f & oldy=%f\n", screen_coord.x, screen_coord.y, (2.0f * count.x) / resolution.x - 1.0f, (-2.0f * count.y) / resolution.y + 1.0f);
			ray = make_ray(origin, target, screen_coord);
			if (intersections(&ray, &shapes, 1))
				mlx_pixel_put_fast(data, count.x, count.y, ray.color);
			count.x++;
		}
		count.y++;
	}
}

// IMPORTANT RAJOUTER LE STARTPOINT DU RAY A TOUT LES CALCULS DE HITPOINTS

int main(int argc, char *argv)
{
	t_vars vars;
	t_data img;
	t_2d res;
	t_shapes shapes;
	res.x = 1200.f;
	res.y = 720.f;
	if (argc != 2)
	{
		printf("error argument\n");
		return (0);
	}
	parsfile(argv[1], &res, &shapes);

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "MiniRT");
	img = new_img(&vars, res.y, res.x);

	project(&img, res, 0xFF0000);
	ft_putstr_fd("finished\n", 1);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
