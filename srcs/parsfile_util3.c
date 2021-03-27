/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile_util3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:05:48 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/27 16:11:15 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		itof_read(char *str, int *i, float *result, int *j)
{
	int flag;

	flag = 0;
	while (str[*i] && (ft_isdigit(str[*i]) || str[*i] == '.'))
	{
		if (ft_isdigit(str[*i]))
		{
			*result = (*result * 10) + str[*i] - '0';
			if (flag)
				(*j)--;
		}
		else if (str[*i] == '.')
		{
			if (flag)
				return (0);
			flag = 1;
		}
		else
			return (0);
		(*i)++;
	}
	return (1);
}

float	itof(char *str, int *i)
{
	float	result;
	int		isneg;
	int		j;

	isneg = 0;
	j = 0;
	result = 0;
	if (str[*i] == '-')
	{
		isneg = 1;
		(*i)++;
	}
	if (!itof_read(str, i, &result, &j))
		return (0);
	result *= pow(10, j);
	if (isneg)
		result *= -1;
	return (result);
}

int		check_name(char *file)
{
	int i;

	i = ft_strlen(file);
	if (i <= 3)
	{
		printf("Error\n%sstrange file...but i can't read that captain", file);
		return (0);
	}
	if (file[i - 1] != 't' || file[i - 2] != 'r' || file[i - 3] != '.')
	{
		printf("Error\nhey your thing don't have a .rt captain");
		return (0);
	}
	return (1);
}
