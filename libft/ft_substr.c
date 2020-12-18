/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:13:27 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/15 20:05:14 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	k;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	k = ft_strlen(&s[start]);
	if (k > len)
		k = len;
	if ((result = malloc((k + 1) * sizeof(char))))
		ft_strlcpy(result, &s[start], k + 1);
	return (result);
}
