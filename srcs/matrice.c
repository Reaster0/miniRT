/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:17:17 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/16 17:18:59 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d v_matrix(t_3d vector, float **matrix)
{
	t_3d result;

	result.x = vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0];
	result.y = vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1];
	result.z = vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2];
}

t_3d p_matrix(t_3d point, float **matrix)
{
	t_3d result;
	result.x = point.x * matrix[0][0] + point.y * matrix[1][0] + point.z * matrix[2][0] + matrix[3][0];
	result.y = point.x * matrix[0][1] + point.y * matrix[1][1] + point.z * matrix[2][1] + matrix[3][1];
	result.z = point.x * matrix[0][2] + point.y * matrix[1][2] + point.z * matrix[2][2] + matrix[3][2];
	result.w = point.x * matrix[0][3] + point.y * matrix[1][3] + point.z * matrix[2][3] + matrix[3][3];
	if (result.w != 1 && result.w != 0)
	{
		result.x /= result.w;
		result.y /= result.w;
		result.z /= result.w;
	}
	return (result);
}

float **scale_mtrx(t_3d point)
{
	float result[3][3];
	result[0][0] = point.x;
	result[0][1] = 0;
	result[0][2] = 0;
	result[0][3] = 0;
	result[1][0] = 0;
	result[1][1] = point.y;
	result[1][2] = 0;
	result[1][3] = 0;
	result[2][0] = 0;
	result[2][1] = 0;
	result[2][2] = point.z;
	result[2][3] = 0;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
	return (result);
}

float **rota_x_mtrx(float angle)
{
	float result[3][3];

	result[0][0] = 1;
	result[0][1] = 0;
	result[0][2] = 0;
	result[0][3] = 0;
	result[1][0] = 0;
	result[1][1] = cos(angle);
	result[1][2] = sin(angle);
	result[1][3] = 0;
	result[2][0] = 0;
	result[2][1] = sin(angle);
	result[2][2] = cos(angle);
	result[2][3] = 0;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
	return (result);
}

float **rota_y_mtrx(float angle)
{
	float result[3][3];

	result[0][0] = cos(angle);
	result[0][1] = 0;
	result[0][2] = sin(angle);
	result[0][3] = 0;
	result[1][0] = 0;
	result[1][1] = 1;
	result[1][2] = 0;
	result[1][3] = 0;
	result[2][0] = sin(angle);
	result[2][1] = 0;
	result[2][2] = cos(angle);
	result[2][3] = 0;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
	return (result);
}

float **rota_z_mtrx(float angle)
{
	float result[3][3];

	result[0][0] = cos(angle);
	result[0][1] = sin(angle);
	result[0][2] = 0;
	result[0][3] = 0;
	result[1][0] = sin(angle);
	result[1][1] = cos(angle);
	result[1][2] = 0;
	result[1][3] = 0;
	result[2][0] = 0;
	result[2][1] = 0;
	result[2][2] = 1;
	result[2][3] = 0;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
	return (result);
}

void fillcol(float *matrix, t_3d data)
{
	matrix[0] = data.x;
	matrix[1] = data.y;
	matrix[2] = data.z;
	matrix[3] = data.w;
}

void outcol(float *matrix, t_3d *data)
{
	data->x = matrix[0];
	data->y = matrix[1];
	data->z = matrix[2];
	data->w = matrix[3];
}

float **multi_mtrx(float **m1, float **m2)
{
	int i;
	int temp;
	int j;
	float result[3][3];

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			temp = 0;
			while (temp < 4)
			{
				result[i][j] = m1[i][temp] * m2[temp][j];
				temp++;
			}
			j++;
		}
		i++;
	}
	return (result);
}