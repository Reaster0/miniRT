/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:17:17 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/17 20:33:14 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_matrix4	cam_to_world(t_camera camera)
{
	t_matrix4 result;

	result.r1 = camera.right;
	result.r2 = camera.up;
	result.r3 = camera.forward;
	result.r4 = camera.startpoint;
	result.r4.w = 1.f;
	return (result);
}

t_3d		v_matrix(t_3d point, t_matrix4 matrix)
{
	t_3d result;

	result.x = point.x * matrix.r1.x + point.y * matrix.r2.x +
		point.z * matrix.r3.x + matrix.r4.x;
	result.y = point.x * matrix.r1.y + point.y * matrix.r2.y +
		point.z * matrix.r3.y + matrix.r4.y;
	result.z = point.x * matrix.r1.z + point.y * matrix.r2.z +
		point.z * matrix.r3.z + matrix.r4.z;
	return (result);
}

t_3d		p_matrix(t_3d point, t_matrix4 matrix)
{
	t_3d result;

	result.x = point.x * matrix.r1.x + point.y * matrix.r2.x +
		point.z * matrix.r3.x + matrix.r4.x;
	result.y = point.x * matrix.r1.y + point.y * matrix.r2.y +
		point.z * matrix.r3.y + matrix.r4.y;
	result.z = point.x * matrix.r1.z + point.y * matrix.r2.z +
		point.z * matrix.r3.z + matrix.r4.z;
	result.w = point.x * matrix.r1.w + point.y * matrix.r2.w +
		point.z * matrix.r3.w + matrix.r4.w;
	return (result);
}
