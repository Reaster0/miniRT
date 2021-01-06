/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:06:33 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/03 19:10:43 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*pdest;
	const unsigned char	*psrc;

	psrc = src;
	pdest = dest;
	i = n;
	if (dest > src)
	{
		while (i)
		{
			i--;
			pdest[i] = psrc[i];
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
