/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:44:55 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 14:56:58 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_3d	all_color(int color, int ray_color, int col_light)
{
	t_3d result;

	result.x = color;
	result.y = ray_color;
	result.z = col_light;
	return (result);
}

void		inter_light(t_ray *ray, t_light *light, t_shapes *shapes)
{
	int		rgb[3];
	t_ray	l_ray;

	light->hit = calculate(*ray, ray->t - 0.0001);
	light->normale = ray->shape_normale;
	l_ray.startpoint = light->hit.endpoint;
	l_ray.endpoint = get_norm(sub_product(light->point, light->hit.endpoint));
	l_ray.t = 1.0e30f;
	l_ray.color = 0.f;
	intersections(&l_ray, shapes, 0);
	if (sqr(l_ray.t) >= length2(sub_product(light->point, light->hit.endpoint)))
	{
		rgb[0] = intens_color(ray, light, all_color(get_r(ray->shape_color),
					get_r(ray->color), (light->intens / 255)
					* get_r(light->color)));
		rgb[1] = intens_color(ray, light, all_color(get_g(ray->shape_color),
					get_g(ray->color), (light->intens / 255)
					* get_g(light->color)));
		rgb[2] = intens_color(ray, light, all_color(get_b(ray->shape_color),
					get_b(ray->color), (light->intens / 255)
					* get_b(light->color)));
		ray->color = create_trgb(get_t(ray->shape_color),
				rgb[0], rgb[1], rgb[2]);
	}
}

void		inter_lights(t_ray *ray, t_light *light, t_shapes *shapes)
{
	while (light)
	{
		inter_light(ray, light, shapes);
		light = light->next;
	}
}
