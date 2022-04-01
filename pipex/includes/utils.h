/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:43:55 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 12:19:43 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <fcntl.h>

# include "vars.h"
# include "libft/libft.h"
# include "get_next_line.h"

int		strdelcpy(char *s1, char *s2, int del);
int		open_file(char *name, int mode);
void	free_char_ptrarr(char **ptrarr);
void	free_char_ptr2d(char **ptr2d);
void	transfer_data(int fd_src, int fd_target);
void	error_exit(char *str);
int		***get_pipes(int cmd_num);
void	cmd_not_found(char *cmd);

#endif
