/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:31:58 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/17 19:13:04 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free_neo(char **neo)
{
	size_t i;

	i = 0;
	if (neo)
	{
		while (neo[i])
			free(neo[i++]);
		free(neo);
	}
	return (0);
}

static size_t	ft_strllen(char const *s, size_t start, char c)
{
	size_t i;

	i = 0;
	while (s[start] && s[start] != c)
	{
		i++;
		start++;
	}
	return (i);
}

static size_t	ft_nbrword(char const *s, char c)
{
	size_t i;
	size_t result;

	i = 0;
	result = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			result++;
		while (s[i] != c && s[i])
			i++;
	}
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	words;

	words = ft_nbrword(s, c);
	i = 0;
	j = 0;
	k = 0;
	if (!(result = malloc((words + 1) * sizeof(char *))))
		return (ft_free_neo(result));
	while (i < words)
	{
		k += j;
		while (s[k] == c)
			k++;
		j = ft_strllen(s, k, c);
		if (!(result[i] = ft_substr(s, k, j)))
			return (ft_free_neo(result));
		i++;
	}
	result[words] = 0;
	return (result);
}
