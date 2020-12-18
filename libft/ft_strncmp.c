/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:07:22 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/15 20:05:00 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && str1[i] == str2[i] && str1[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
