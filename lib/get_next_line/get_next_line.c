/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:48 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 18:50:31 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_index(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_line(char **str_read, char **line, int index)
{
	int	len;

	*line = ft_substr_gnl(*str_read, 0, index);
	len = ft_strlen_gnl(*str_read + index + 1) + 1;
	ft_memmove_gnl(*str_read, *str_read + index + 1, len);
	if (*str_read && *str_read[0] == '\0')
	{
		free(*str_read);
		*str_read = NULL;
	}
	return (1);
}

int	get_next_line_first(char **line, int fd, char *buf)
{
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	else
		return (1);
}

int	get_next_line(int fd, char **line)
{
	int			byt_read;
	static char	*s_read[FD_SIZE];
	char		buf[BUFFER_SIZE + 1];

	get_next_line_first(line, fd, buf);
	if (s_read[fd] && get_index(s_read[fd], '\n') != -1)
		return (get_line(&s_read[fd], line, get_index(s_read[fd], '\n')));
	byt_read = read(fd, buf, BUFFER_SIZE);
	while (byt_read > 0)
	{
		buf[byt_read] = '\0';
		s_read[fd] = ft_joinstr_gnl(s_read[fd], buf);
		if (get_index(s_read[fd], '\n') != -1)
			return (get_line(&s_read[fd], line, get_index(s_read[fd], '\n')));
		byt_read = read(fd, buf, BUFFER_SIZE);
	}
	if (s_read[fd])
	{
		*line = ft_strdup_gnl(s_read[fd]);
		free(s_read[fd]);
		s_read[fd] = NULL;
	}
	else
		*line = ft_strdup_gnl("");
	return (0);
}
