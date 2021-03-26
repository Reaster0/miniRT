/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:22:04 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/09 16:21:53 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d	new_3d(float x, float y, float z)
{
	t_3d result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 0;
	return (result);
}

t_2d	new_2d(float x, float y)
{
	t_2d result;

	result.x = x;
	result.y = y;
	return (result);
}
