/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:37:46 by soekim            #+#    #+#             */
/*   Updated: 2022/05/14 15:26:57 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# define P_TO_C	0
# define C_TO_P	1

# define RD		0
# define WR		1

# define STDIN	0
# define STDOUT	1

# define CHILD	0

# define TRUE	1
# define FALSE	0

# include "../libft/libft.h"

int		g_exit_status;

typedef struct s_arg
{
	int		cnt;
	char	**vec;
}				t_arg;

typedef struct s_file
{
	int		fd;
	int		o_flag;
}				t_file;

typedef struct s_cmd_info
{
	int		in_fd;
	int		out_fd;
	char	*out_name;
	char	**cmd_args;
}				t_cmd_info;

typedef struct s_token
{
	char	*cmd;
	char	redir_flag;
}				t_token;

typedef struct s_cmd_list
{
	t_token				*tokens;
	int					flag;
	char				*(redir_file[4]);
	int					pipe_flag;
	int					exit_flag;
	struct s_cmd_list	*next;
}				t_cmd;

#endif
