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

# define PTOC	0
# define CTOP	1

# define RD		0
# define WR		1

# define STDIN	0
# define STDOUT	1

# define CHILD	0

# define TRUE	1
# define FALSE	0

# include "libft/libft.h"

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

// struct	s_inout
// {
// 	t_file	in;
// 	t_file	out;
// };
// typedef struct s_inout	t_inout;

struct s_token_info
{
	int input;
	int output;
	char **cmd_arg;
};
typedef struct s_token_info t_token_info;


#endif