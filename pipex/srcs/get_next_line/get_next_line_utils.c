/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:32:19 by soekim            #+#    #+#             */
/*   Updated: 2021/06/18 22:36:17 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_strcpy(char *dst, const char *src)
{
	if (!dst || !src)
		return (dst);
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (dst);
}

char	*ft_strncpy(char *dst, const char *src, int len)
{
	if (!dst || !src)
		return (dst);
	while (*src && --len >= 0)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (dst);
}

int	strdel_len(char *s, char delimiter)
{
	int		len;

	if (!s)
		return (0);
	len = 0;
	while (*s && *s != delimiter)
	{
		s++;
		len++;
	}
	return (len);
}

int	strcat_del(char **line, char *to_catenate, char delimiter)
{
	int		cat_len;
	char	*tab;
	char	*newstr;

	if (!to_catenate)
		return (0);
	cat_len = strdel_len(to_catenate, delimiter);
	newstr = (char *)malloc(strdel_len(*line, '\0') + cat_len + 1);
	if (!newstr)
		return (ERROR);
	tab = ft_strcpy(newstr, *line);
	tab = ft_strncpy(tab, to_catenate, cat_len);
	*tab = '\0';
	if (*line)
		free(*line);
	*line = newstr;
	return (cat_len);
}
