/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:34:41 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 13:25:15 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "utils.h"
# include "structs.h"

int		is_correct_path(char *path, char *cmd);
char	*find_cmdpath(char *cmd, char **envp);
char	**read_cmd_arg(int fd);

#endif
