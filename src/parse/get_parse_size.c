/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:18 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 01:15:53 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	get_parse_size(char *cmd, char **envp)
{
	int		size;
	int		index;
	char	*tmp;

	size = 0;
	index = -1;
	while (cmd[++index])
	{
		if (cmd[index] == '\'' && check_unclosed_quote(&cmd[index], '\''))
			index += squote_cnt(&cmd[index], &size);
		else if (cmd[index] == '\"' && check_unclosed_quote(&cmd[index], '\"'))
			index += dquote_cnt(&cmd[index], &size, envp);
		else if (cmd[index] == '$')
			index += env_len(&cmd[index], &size, envp);
		else if (cmd[index])
			++size;
	}
	printf("parse size: %d\n", size);
	return (size);
}
