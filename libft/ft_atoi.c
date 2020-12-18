/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:55:14 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/15 20:02:54 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	int				i;
	long long int	result;
	int				negative;

	negative = 1;
	i = 0;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n' ||
			nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
		negative = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		result += nptr[i] - '0';
		result *= ft_isdigit(nptr[++i]) ? 10 : 1;
		if (result < 0)
			return (negative == 1 ? -1 : 0);
	}
	return ((int)result * negative);
}
