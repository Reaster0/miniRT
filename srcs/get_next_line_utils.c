/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:23:32 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/05 13:28:12 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char *ft_strjoin_sp(char **s1, char const *s2)
{
	char *result;
	char *temp;

	if (!(temp = ft_strdup(*s1)))
		return (0);
	free(*s1);
	if (!(result = malloc((ft_strlen(temp) + ft_strlen(s2) + 1) * sizeof(char))))
	{
		free(temp);
		return (0);
	}
	ft_strlcpy(result, temp, ft_strlen(temp) + 1);
	ft_strlcpy(result + ft_strlen(temp), s2, ft_strlen(s2) + 1);
	free(temp);
	return (result);
}

size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (!dest)
		return (0);
	if (size)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (ft_strlen(src));
}

size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
	char *result;

	if (!(result = malloc((ft_strlen(s) + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(result, s, ft_strlen(s) + 1);
	return (result);
}

long int ft_line(const char *s)
{
	size_t i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}
