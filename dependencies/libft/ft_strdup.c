/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:06:11 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/13 15:08:39 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *result;

	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	ft_strlcpy(result, s, ft_strlen(s) + 1);
	return (result);
}
