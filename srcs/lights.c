/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:44:55 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/17 20:52:41 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light *new_light(t_3d point, int intens)
{
	t_light *light;
	light = malloc(sizeof(t_light));
	light->point = point;
	light->intens = intens;
	return (light);
}

void inter_light(t_ray *ray, t_light *light, t_shapes *shapes)
{
	light->hit = calculate(*ray, ray->t);
	light->normale = ray->shape_normale;

	t_ray l_ray;
	//maybe multiply by 0.9
	l_ray.startpoint = add_product(multiply_v(0.1f, light->normale), light->hit.endpoint);
	//maybe get_norm
	l_ray.endpoint = sub_product(light->point, light->hit.endpoint);
	l_ray.t = 1.0e30f;
	l_ray.color = 0;

	intersections(&l_ray, shapes, 0);
	if (sqr(l_ray.t) > length2(sub_product(light->point, light->hit.endpoint)))
	{ //gerer la couleur de la lumiere
		int r = intens_color(ray, light, get_r(ray->shape_color), get_r(ray->color));
		int g = intens_color(ray, light, get_g(ray->shape_color), get_g(ray->color));
		int b = intens_color(ray, light, get_b(ray->shape_color), get_b(ray->color));

		ray->color = create_trgb(get_t(ray->shape_color), r, g, b);
	}
}

void inter_lights(t_ray *ray, t_light **light, t_shapes *shapes)
{
	int i;
	i = 0;
	while (light[i])
	{
		inter_light(ray, light[i], shapes);
		i++;
	}
}