/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:14:41 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/11 18:53:52 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*result;

	j = ft_strlen(s1);
	i = 0;
	if (!s1 || !set)
		return (0);
	while (s1[i] && ft_strchr((char *)set, s1[i]))
		i++;
	while (j && j > i && ft_strchr((char *)set, s1[j]))
		j--;
	result = ft_substr(s1, i, j - i + 1);
	return (result);
}
