/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:48:55 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/07 16:53:06 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char *ft_afterline(char *s)
{
	char *temp;

	if (!(ft_line(s) + 1))
		return (NULL);
	temp = ft_strdup(s + ft_line(s) + 1);
	free(s);
	return (temp);
}

int ft_check_error(char **line, int fd)
{
	char buf[1];

	if (fd < 0 || !line || read(fd, buf, 0) == -1)
		return (-1);
	return (1);
}

int ft_sendline_next(char **line, char *rest)
{
	size_t len;

	if (ft_line(rest) == -1)
		len = ft_strlen(rest);
	else
		len = ft_line(rest);
	if (!(*line = malloc((len + 1) * sizeof(char *))))
		return (-1);
	ft_strlcpy(*line, rest, len + 1);
	return (1);
}

int ft_read_buf(char **rest, char **line, int fd)
{
	char buf[42 + 1];
	int read_ret;
	int ret;

	ret = 1;
	while (ft_line(*rest) == -1)
	{
		read_ret = read(fd, buf, 42);
		if (!read_ret)
		{
			if (ft_line(*rest) == -1)
				ret = 0;
			break;
		}
		buf[read_ret] = '\0';
		if (!(*rest = ft_strjoin_sp(&*rest, buf)))
			return (-1);
	}
	if (ft_sendline_next(line, *rest) == -1)
		return (-1);
	if (ft_line(*rest) + 1)
		if (!(*rest = ft_afterline(*rest)))
			return (-1);
	return (ret);
}

int get_next_line(int fd, char **line)
{
	static char *rest[FOPEN_MAX];
	int ret;

	ret = 1;
	if (ft_check_error(line, fd) == -1)
		return (-1);
	if (!rest[fd])
		rest[fd] = ft_strdup("");
	if (ft_line(rest[fd]) >= 0)
	{
		if (!(*line = malloc(ft_line(rest[fd]) * sizeof(char *))))
			return (-1);
		ft_strlcpy(*line, rest[fd], ft_line(rest[fd]) + 1);
		if (rest[fd] + ft_line(rest[fd]) + 1)
			rest[fd] = ft_afterline(rest[fd]);
	}
	else
	{
		if (!(ret = ft_read_buf(&rest[fd], line, fd)))
		{
			free(rest[fd]);
			rest[fd] = NULL;
		}
	}
	return (ret);
}
