/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:51:00 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/09 15:43:29 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && *(const unsigned char *)(s1 + i) ==
				*(const unsigned char *)(s2 + i))
		i++;
	if (i == n)
		return (0);
	return (*(const unsigned char *)(s1 + i) -
				*(const unsigned char *)(s2 + i));
}
