/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:45:13 by soekim            #+#    #+#             */
/*   Updated: 2021/07/01 22:53:21 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define END_OF_FDS -1

# include <unistd.h>

# include "vars.h"
# include "utils.h"
# include "parse.h"
# include "structs.h"
# include "inout.h"

void	exec_arg(t_cmd_list *cmd_list, char **envp);
void	exec_cmd(t_token_info *token_info, char **envp, int (*pipes)[2]);

#endif
