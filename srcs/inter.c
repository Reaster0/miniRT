/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:18:07 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 14:57:09 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			intens_color(t_ray *ray, t_light *light, t_3d all_color)
{
	float	temp;
	int		result;

	temp = ((all_color.x / 255) * ((int)all_color.z *
				dot_product(get_norm(sub_product(light->point,
							light->hit.shape_point)),
					light->hit.shape_normale) /
				length2(sub_product(light->point,
						light->hit.endpoint))));
	result = temp * 255;
	if (result > 255)
		result = 255;
	if (result < (int)all_color.y)
		result = (int)all_color.y;
	return (result);
}

int			intersections(t_ray *ray, t_shapes *shapes, int inter_l)
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

void		project(t_data *data, t_2d res, t_shapes *shapes, t_camera *camera)
{
	float	i;
	t_2d	count;
	t_3d	screen_coord;
	t_ray	ray;

	count.y = 0;
	while (count.y < res.y)
	{
		count.x = -1;
		while (++count.x < res.x)
		{
			screen_coord.x = 2 * ((count.x + 0.5) / res.x) - 1.f;
			screen_coord.y = 1 - 2 * ((count.y + 0.5) / res.y);
			screen_coord.x *= tan(camera->fov);
			screen_coord.y *= tan(camera->fov);
			screen_coord.x *= res.x / res.y;
			screen_coord.z = -1.f;
			printf("\rLoading (%.0f%%)", (count.y / res.y) * 100);
			ray = make_ray(camera->startpoint, camera->forward, screen_coord
					, shapes->ambient);
			if (intersections(&ray, shapes, 1))
				mlx_pixel_put_fast(data, count.x, count.y, ray.color);
		}
		count.y++;
	}
}

void		process_fullinter(t_vars *vars
			, t_data *img, t_all *all, t_shapes *shapes)
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
