/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:14:14 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 17:29:55 by hnoh             ###   ########.fr       */
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
	int		i;

	i = argc;
	argc = i;
	copied_env = NULL;
	argv = copied_env;
	copied_env = copy_envp(envp);
	signal_init();
	while (1)
	{
		line = readline("minishell $ ");
		if (line == NULL)
			break ;
		if (*line != '\0' && !check_whitespace(line))
		{
			add_history(line);
			parse(&cmds, line, envp);
			// system("leaks minishell");
			exec(cmds, &copied_env);
			system("leaks minishell");

			free_cmds(cmds);
			// free(line);
		}
		g_exit_status = 0;
        free(line);
		// system("leaks minishell");
	}
	free_copied_env(copied_env);
    system("leaks minishell");
	return (0);
}
