/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:08:24 by soekim            #+#    #+#             */
/*   Updated: 2021/07/02 15:10:23 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inout.h"

void	init_inout(t_inout *inout, t_arg *arg)
{
	ft_memset(inout, sizeof(t_inout), 0);
	inout->in.o_flag = O_RDONLY;
	inout->in.fd = open_file(arg->vec[1], inout->in.o_flag);
	inout->out.o_flag = O_RDWR | O_CREAT | O_TRUNC;
	if (arg->cnt > 4)
		inout->out.fd = open_file(arg->vec[arg->cnt - 1], inout->out.o_flag);
	else
		inout->out.fd = STDOUT;
	return ;
}
