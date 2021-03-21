/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:35:34 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/21 18:03:56 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_matrix4 lookat(t_3d origin, t_3d target)
{ //gerer mieux le cas ou forward y  = 1
	t_camera result;
	result.startpoint = origin;
	//target = add_product(target, origin);
	result.forward = get_norm(sub_product(origin, target));
	if (result.forward.y == 1)
		result.forward.y -= 0.001f;
	if (result.forward.y == -1)
		result.forward.y += 0.001f;
	result.right = cross_product(get_norm(new_3d(0.f, 1.f, 0.f)), result.forward);
	result.up = cross_product(result.forward, result.right);

	return (cam_to_world(result));
}

t_ray make_ray(t_3d origin, t_3d target, t_3d screen, int ambient)
{
	t_ray ray;
	t_matrix4 temp;
	ray.startpoint = origin;

	temp = lookat(origin, add_product(origin, target));

	ray.endpoint = v_matrix(screen, temp);
	ray.endpoint = (sub_product(ray.endpoint, origin));
	normalize(&ray.endpoint);
	ray.t = 1.0e30f;
	ray.color = ambient;
	return (ray);
}