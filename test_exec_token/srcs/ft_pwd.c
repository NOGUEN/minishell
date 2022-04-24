/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:38:03 by djeon             #+#    #+#             */
/*   Updated: 2021/07/03 16:03:53 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_pwd(int fd)
{
	char		*str;

	str = getcwd(NULL, 0);
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
	free(str);
	return (1);
}