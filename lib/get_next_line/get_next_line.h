/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:57 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/21 15:54:44 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define FD_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int			get_next_line(int fd, char **line);
int			find_index(const char *s, int c);
int			get_line(char **str, char **line, int i);
char		*ft_joinstr_gnl(char *s1, char *s2);
char		*ft_strdup_gnl(const char *s1);
char		*ft_substr_gnl(char const *s, int start, int len);
void		*ft_memmove_gnl(void *dst, const void *src, size_t len);
size_t		ft_strlen_gnl(const char *s);

#endif
