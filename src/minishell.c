/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:14:14 by noguen            #+#    #+#             */
/*   Updated: 2022/05/15 17:51:35 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*free_cmd;
	t_token	*free_tokens;
	int		index;

	index = -1;
	while (cmds)
	{
		free_cmd = cmds;
		cmds = cmds->next;
		free_tokens = free_cmd->tokens;
		while (free_tokens->cmd)
		{
			free(free_tokens->cmd);
			free_tokens++;
		}
		free(free_cmd->tokens);
		free(free_cmd);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmds;
	char	*line;
	char	**copied_env;

	if (!argc || !argv)
		return (0);
	copied_env = copy_envp(envp);
	signal_init();
	while (TRUE)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line != '\0' && !check_whitespace(line))
		{
			add_history(line);
			parse(&cmds, line, envp);
			exec(cmds, &copied_env);
			free_cmds(cmds);
			free(line);
		}
	}
	printf("\x1b[1A\033[12Cexit\n");
	free_copied_env(copied_env);
	return (0);
}
