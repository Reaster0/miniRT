/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:07:33 by earnaud           #+#    #+#             */
/*   Updated: 2020/11/08 19:10:04 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int i;

	i = ft_strlen(str) + 1;
	while (i)
	{
		i--;
		if (c == str[i])
			return (&str[i]);
	}
	return (0);
}
