/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:44:55 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/09 16:24:14 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void inter_light(t_ray *ray, t_light *light, t_shapes *shapes)
{
	light->hit = calculate(*ray, ray->t);
	light->normale = ray->shape_normale;

	t_ray l_ray;
	//maybe multiply by 0.9
	l_ray.startpoint = add_product(multiply_v(0.9f, light->normale), light->hit.endpoint);
	//maybe get_norm
	l_ray.endpoint = get_norm(sub_product(light->point, light->hit.endpoint));
	l_ray.t = 1.0e30f;
	l_ray.color = 0.f;
	//printf("hitpoint x=%f,y=%f,z=%f\n", light->hit.endpoint.x, light->hit.endpoint.y, light->hit.endpoint.z);

	//printf("t =%f\n", ray->t);
	intersections(&l_ray, shapes, 0);
	if (sqr(l_ray.t) > length2(sub_product(light->point, light->hit.endpoint)))
	{ //gerer la couleur de la lumiere
		int r = intens_color(ray, light, get_r(ray->shape_color), get_r(ray->color));
		int g = intens_color(ray, light, get_g(ray->shape_color), get_g(ray->color));
		int b = intens_color(ray, light, get_b(ray->shape_color), get_b(ray->color));

		ray->color = create_trgb(get_t(ray->shape_color), r, g, b);
	}
}

void inter_lights(t_ray *ray, t_light *light, t_shapes *shapes)
{
	while (light)
	{
		inter_light(ray, light, shapes);
		light = light->next;
	}
}