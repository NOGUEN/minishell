/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:45:13 by soekim            #+#    #+#             */
/*   Updated: 2022/05/14 12:59:26 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define END_OF_FDS -1
# define CD_FAILED -1

# include <unistd.h>
# include "vars.h"
# include "utils.h"
# include "parse.h"
# include "cmd_info.h"
# include "built_in.h"

void	exec(t_cmd *cmd_list, char ***envp);
void	fork_and_exec(t_cmd_info *cmd_info, char **envp, int (*pipes)[2]);
void	exec_cmd(t_cmd_info *cmd_info, char **envp, int (*pipes)[2]);

#endif
