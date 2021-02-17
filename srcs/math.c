/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:15:31 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/17 20:58:43 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// t_camera world_to_cam(t_matrix4 matrix, t_3d from)
// {
// 	t_camera camera;
// 	camera.right = matrix.r1;
// 	camera.up = matrix.r2;
// 	camera.forward = matrix.r3;
// 	camera.startpoint = matrix.r4;
// 	return (camera);
// }

// t_camera new_camera(t_3d origin, t_3d target)
// {
// 	t_camera result;
// 	result.zero = new_3d(0.f, 0.f, 0.f);
// 	// result.forward = get_norm(sub_product(result.startpoint, target));
// 	result.right = cross_product(get_norm(new_3d(0.f, 1.f, 0.f)), result.forward);
// 	if (result.forward.y == 1 && !result.forward.x && !result.forward.z)
// 		result.forward.y -= 0.001;
// 	if (result.forward.y == -1 && !result.forward.x && !result.forward.z)
// 		result.forward.y += 0.001;
// 	return (result);
// }