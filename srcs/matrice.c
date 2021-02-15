/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:17:17 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/15 19:28:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d p_matrix(t_3d point, float **matrix)
{
	t_3d result;
	result.x = point.x * matrix[0][0] + point.y * matrix[1][0] + point.z * matrix[2][0];
	result.y = point.x * matrix[0][1] + point.y * matrix[1][1] + point.z * matrix[2][1];
	result.z = point.x * matrix[0][2] + point.y * matrix[1][2] + point.z * matrix[2][2];
}

void fillcol(float *matrix, t_3d data, float i)
{
	matrix[0] = data.x;
	matrix[1] = data.y;
	matrix[2] = data.z;
	matrix[3] = i;
}

void outcol(float *matrix, t_3d *data)
{
	data->x = matrix[0];
	data->y = matrix[1];
	data->z = matrix[2];
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