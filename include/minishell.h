/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:56:42 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 12:58:38 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "exec.h"
# define BEGIN 0x00000001
# define SQUOTE 0x00000002
# define DQUOTE 0x00000004
# define REDIR 0x00000008
# define COUNT 0x000000010
# define QUOTE 0x000000020
# define PIPE 0x000000040

extern int	g_exit_status;

/* signal */
void	signal_sigint(int signo);
void	signal_sigquit(int signo);
void	signal_init(void);

#endif
