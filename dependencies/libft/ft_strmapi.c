/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:13:47 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/14 16:17:42 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*result;

	i = -1;
	if (!(result = malloc((ft_strlen(s) + 1) * sizeof(char))))
		return (0);
	while (s[++i])
		result[i] = f(i, s[i]);
	result[i] = 0;
	return (result);
}
