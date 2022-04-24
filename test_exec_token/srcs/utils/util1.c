/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:12:16 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 12:19:31 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	strdelcpy(char *s1, char *s2, int del)
{
	while (*s1 && *s2 && *s1 != del && *s2 != del)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		++s1;
		++s2;
	}
	if (*s1 == del || *s2 == del)
		return (0);
	else
		return (*s1 - *s2);
}

void	error_exit(char *str)
{
	ft_putendl_fd(str, STDOUT);
	exit(1);
}

int	open_file(char *name, int mode)
{
	int		fd;

	if (!name)
		return (-1);
	fd = open(name, mode);
	if (fd < 0)
	{
		printf("faield open:\n");
		exit(0);
	}
	return (fd);
}