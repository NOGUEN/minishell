/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:14:14 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 01:14:18 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*to_free;

	while (cmds)
	{
		to_free = cmds;
		cmds = cmds->next;
		free(to_free);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmds;
	char	*line;
	char	**copied_env;

	copied_env = copy_envp(envp);
	signal_init();
	while (line = readline("minishell $ "))
	{
		if (*line != '\0' && !check_whitespace(line))
		{
			add_history(line);
			parse(&cmds, line, envp);
			exec(cmds, &copied_env);
			free_cmds(cmds);
			free(line);
		}
		printf("g%d\n", g_exit_status);
		g_exit_status = 0;
	}
	free_copied_env(copied_env);
	return (0);
}
