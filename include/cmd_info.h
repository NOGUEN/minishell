/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:50:37 by soekim            #+#    #+#             */
/*   Updated: 2021/06/26 17:08:21 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_INFO_H 
# define CMD_INFO_H

# define NO_DATA -1

# include "vars.h"
# include "utils.h"
# include "structs.h"

# include <fcntl.h>
# include <readline/readline.h>

void init_cmd_info(t_cmd_info *info, t_token *token, int (*pipes)[2]);
#endif
