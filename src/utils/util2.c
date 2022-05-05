/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 20:02:56 by soekim            #+#    #+#             */
/*   Updated: 2021/07/09 16:16:18 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	free_char_ptrarr(char **ptrarr)
{
	while (*ptrarr)
	{
		free(*ptrarr);
		++ptrarr;
	}
	return ;
}

void	free_char_ptr2d(char **ptr2d)
{
	free_char_ptrarr(ptr2d);
	free(ptr2d);
	return ;
}

void	cmd_not_found(char *cmd)
{
	write(1, "\n", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	exit(0);
}