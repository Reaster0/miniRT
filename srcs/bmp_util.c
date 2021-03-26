/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:13:45 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/26 14:26:21 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		check_error(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "--save", 6) != 0)
	{
		printf("Error\nargument must be save, captain");
		return (0);
	}
	return (1);
}

int		get_opposite(int color)
{
	return (0xFFFFFF - color);
}
