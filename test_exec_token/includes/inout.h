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

#ifndef INOUT_H
# define INOUT_H

# define NO_DATA -1

# include "vars.h"
# include "utils.h"
# include "structs.h"

# include <fcntl.h>

void init_token_info(t_token_info *info, t_token *token);
#endif