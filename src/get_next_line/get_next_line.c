/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:21:20 by opelser           #+#    #+#             */
/*   Updated: 2024/02/22 16:43:42 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static ssize_t	find_newline(char *str)
{
	ssize_t		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

static char	*divide_lines(char *str)
{
	int		i;
	char	*rest;

	i = find_newline(str) + 1;
	if (str[i - 1] == '\0')
		return (NULL);
	rest = ft_strdup(str + i);
	str[i] = '\0';
	return (rest);
}

static char	*make_str(int fd, char *str)
{
	char	buf[BUFFER_SIZE + 1];

	if (!ft_read(fd, buf))
		return (free(str), NULL);
	while (find_newline(buf) == BUFFER_SIZE)
	{
		str = ft_strjoin_replace(str, buf);
		if (!str)
			return (NULL);
		if (!ft_read(fd, buf))
			return (str);
	}
	str = ft_strjoin_replace(str, buf);
	if (!str)
		return (NULL);
	if (str[0] == '\0')
		return (free(str), NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	char			*str;
	static char		*rest;
	char			*new;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = NULL;
	if (rest)
	{
		str = ft_strdup(rest);
		ft_free(&rest);
		if (!str)
			return (NULL);
	}
	rest = NULL;
	str = make_str(fd, str);
	if (!str)
		return (NULL);
	rest = divide_lines(str);
	new = ft_strdup(str);
	free(str);
	if (!new)
		return (ft_free(&rest));
	return (new);
}
