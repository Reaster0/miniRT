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

t_matrix4 cam_to_world(t_camera camera)
{
	t_matrix4 result;
	result.r1 = camera.right;
	result.r2 = camera.up;
	result.r3 = camera.forward;
	result.r4 = camera.startpoint;
	result.r4.w = 1.f;
	// printf("r1 1=%f,2=%f,3=%f,4=%f\n", result.r1.x, result.r1.y, result.r1.z);
	// printf("r2 1=%f,2=%f,3=%f,4=%f\n", result.r2.x, result.r2.y, result.r2.z);
	// printf("r3 1=%f,2=%f,3=%f,4=%f\n", result.r3.x, result.r3.y, result.r3.z);
	// printf("r4 1=%f,2=%f,3=%f,4=%f\n", result.r4.x, result.r4.y, result.r4.z);
	return (result);
}

t_3d v_matrix(t_3d point, t_matrix4 matrix)
{
	t_3d result;
	result.x = point.x * matrix.r1.x + point.y * matrix.r2.x + point.z * matrix.r3.x + matrix.r4.x;
	result.y = point.x * matrix.r1.y + point.y * matrix.r2.y + point.z * matrix.r3.y + matrix.r4.y;
	result.z = point.x * matrix.r1.z + point.y * matrix.r2.z + point.z * matrix.r3.z + matrix.r4.z;
	return (result);
}

t_3d p_matrix(t_3d point, t_matrix4 matrix)
{
	t_3d result;
	result.x = point.x * matrix.r1.x + point.y * matrix.r2.x + point.z * matrix.r3.x + matrix.r4.x;
	result.y = point.x * matrix.r1.y + point.y * matrix.r2.y + point.z * matrix.r3.y + matrix.r4.y;
	result.z = point.x * matrix.r1.z + point.y * matrix.r2.z + point.z * matrix.r3.z + matrix.r4.z;
	result.w = point.x * matrix.r1.w + point.y * matrix.r2.w + point.z * matrix.r3.w + matrix.r4.w;
	// if (result.w != 1 && result.w != 0)
	// {
	// 	result.x /= result.w;
	// 	result.y /= result.w;
	// 	result.z /= result.w;
	// }
	return (result);
}

t_matrix4 scale_mtrx(t_3d point)
{
	t_matrix4 result;
	result.r1 = new_3d(point.x, 0.f, 0.f);
	result.r2 = new_3d(0.f, point.y, 0.f);
	result.r3 = new_3d(0.f, 0.f, point.z);
	result.r4 = new_3d(0.f, 0.f, 0.f);
	result.r4.w = 1;
	return (result);
}

t_matrix4 rota_x_mtrx(float angle)
{
	t_matrix4 result;
	result.r1 = new_3d(1.f, 0.f, 0.f);
	result.r2 = new_3d(0.f, cos(angle), sin(angle));
	result.r3 = new_3d(0.f, sin(angle), cos(angle));
	result.r4 = new_3d(0.f, 0.f, 0.f);
	result.r4.w = 1.f;
	return (result);
}

t_matrix4 rota_y_mtrx(float angle)
{
	t_matrix4 result;
	result.r1 = new_3d(cos(angle), 0.f, sin(angle));
	result.r2 = new_3d(0.f, 1.f, 0.f);
	result.r3 = new_3d(sin(angle), 0.f, cos(angle));
	result.r4 = new_3d(0.f, 0.f, 0.f);
	result.r4.w = 1.f;
	return (result);
}

t_matrix4 rota_z_mtrx(float angle)
{
	t_matrix4 result;
	result.r1 = new_3d(cos(angle), sin(angle), 0.f);
	result.r2 = new_3d(sin(angle), cos(angle), 0.f);
	result.r3 = new_3d(0.f, 0.f, 1.f);
	result.r4 = new_3d(0.f, 0.f, 0.f);
	result.r4.w = 1.f;
	return (result);
}

// float **multi_mtrx(float **m1, float **m2)
// {
// 	int i;
// 	int temp;
// 	int j;
// 	float result[4][4];

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			temp = 0;
// 			while (temp < 4)
// 			{
// 				result[i][j] = m1[i][temp] * m2[temp][j];
// 				temp++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (result);
// }