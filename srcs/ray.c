/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:35:34 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/17 20:37:09 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_matrix4 lookat(t_3d origin, t_3d target)
{ //gerer mieux le cas ou forward y  = 1
	t_camera result;
	result.startpoint = origin;
	//if there is a problem it's here
	target = add_product(target, origin);
	result.forward = get_norm(sub_product(origin, target));
	if (result.forward.y == 1)
		result.forward.y -= 0.001;
	if (result.forward.y == -1)
		result.forward.y += 0.001;
	result.right = cross_product(get_norm(new_3d(0.f, 1.f, 0.f)), result.forward);
	result.up = cross_product(result.forward, result.right);

	//printf("right x=%f,y=%f,z=%f\nforward x=%f,y=%f,z=%f\n", result.right.x, result.right.y, result.right.z, result.forward.x, result.forward.y, result.forward.z);
	return (cam_to_world(result));
}

//new version

t_ray make_ray(t_3d origin, t_3d target, t_3d screen)
{
	t_ray ray;
	t_matrix4 temp;
	ray.startpoint = origin;

	temp = lookat(origin, target);

	ray.endpoint = v_matrix(screen, temp);
	ray.endpoint = (sub_product(ray.endpoint, origin));
	//normalize(&ray.endpoint);

	ray.t = 1.0e30f;
	ray.color = 0;
	return (ray);
}