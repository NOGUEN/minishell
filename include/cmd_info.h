/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:50:37 by soekim            #+#    #+#             */
/*   Updated: 2022/05/14 12:53:15 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CMD_INFO_H 
# define CMD_INFO_H
# define NO_DATA -1
# define ERR_IN_OUT -2
# include "vars.h"
# include "utils.h"

# include <fcntl.h>
# include <readline/readline.h>

void	init_cmd_info(t_cmd_info *info, t_token *token, int (*pipes)[2]);
#endif
