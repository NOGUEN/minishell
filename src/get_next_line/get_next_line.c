/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:32:19 by soekim            #+#    #+#             */
/*   Updated: 2021/06/18 22:36:10 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

int	read_new_line(char **next, char *buffer, int fd)
{
	int	result;

	result = read(fd, buffer, BUFFER_SIZE);
	if (result == ERROR)
		return (ERROR);
	buffer[result] = '\0';
	*next = buffer;
	return (result);
}

int	get_oneline_and_next(char **next, char *buffer, char **temp, int fd)
{
	int	is_oneline;
	int	result;
	int	catlen;

	is_oneline = 0;
	result = 1;
	while (!is_oneline)
	{
		if (!(*next))
			result = read_new_line(next, buffer, fd);
		catlen = strcat_del(temp, *next, '\n');
		if (catlen == ERROR)
			return (ERROR);
		*next += catlen;
		if (**next == '\n' || result == END)
			is_oneline = 1;
		if (**next == '\n')
			*next = *next + 1;
		if (**next == '\0')
			*next = NULL;
	}
	return (result);
}

int	get_next_line(int fd, char **line)
{
	static char	*next;
	static char	buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			result;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	temp = NULL;
	result = get_oneline_and_next(&next, buffer, &temp, fd);
	if (result == ERROR)
		return (ERROR);
	*line = temp;
	if (result == END)
	{
		next = NULL;
		return (END);
	}
	return (SUCCESS);
}
