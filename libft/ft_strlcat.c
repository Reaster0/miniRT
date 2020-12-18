/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:15:17 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/09 15:41:09 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t c;

	i = 0;
	c = 0;
	while (dst[i] && i < size)
		i++;
	while (src[c] && (i + c + 1) < size)
	{
		dst[i + c] = src[c];
		c++;
	}
	if (i < size)
		dst[i + c] = 0;
	return (i + ft_strlen(src));
}
