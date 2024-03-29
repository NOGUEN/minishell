/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:43:55 by soekim            #+#    #+#             */
/*   Updated: 2022/05/15 20:09:39 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <fcntl.h>
# include "vars.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include "cmd_info.h"

int		strdelcmp(char *s1, char *s2, int del);
int		open_file(char *name, int mode);
void	free_char_ptrarr(char **ptrarr);
void	free_char_ptr2d(char **ptr2d);
void	error_exit(char *str);
int		***get_pipes(int cmd_num);
void	cmd_not_found(char *cmd);
char	**sort_env(char **envp);
void	free_copied_env(char **copied);
char	**copy_envp(char **envp);
void	close_fds(t_cmd_info *cmd_info, int (*pipes)[2], int *input);
void	init_fork_pipes(int (*pipes)[2]);
int		strcmp_bfdel(char *s1, char *s2, int del);

#endif
