/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:46:07 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 16:10:39 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

t_cmd	*new_cmd(char *line, int pipe_flag, char **envp, int exit_flag)
{
	t_cmd	*result;

	result = (t_cmd *)malloc(sizeof(t_cmd));
	if (result == NULL)
		return (NULL);
	result->tokens = split_cmd(line);
	alloc_token(result->tokens, envp);
	result->pipe_flag = pipe_flag;
	if (exit_flag == 0 && pipe_flag == 0)
		result->exit_flag = 1;
	else
		result->exit_flag = 0;
	result->next = NULL;
	return (result);
}
