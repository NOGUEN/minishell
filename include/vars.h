/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:37:46 by soekim            #+#    #+#             */
/*   Updated: 2021/07/02 15:39:49 by soekim           ###   ########.fr       */
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

struct	s_arg
{
	int		cnt;
	char	**vec;
};
typedef struct s_arg	t_arg;

struct	s_file
{
	int		fd;
	int		o_flag;
};
typedef struct s_file	t_file;

struct s_cmd_info
{
	int in_fd;
	int out_fd;
	char *out_name;
	char **cmd_args;
};
typedef struct s_cmd_info t_cmd_info;


#endif