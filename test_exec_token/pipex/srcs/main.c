/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:21:29 by soekim            #+#    #+#             */
/*   Updated: 2021/07/09 16:21:31 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	t_inout	inout;

	if (argc <= 4)
		return (0);
	arg.cnt = argc;
	arg.vec = argv;
	init_inout(&inout, &arg);
	exec_arg(&arg, envp, &inout);
	close(inout.out.fd);
	return (0);


}
