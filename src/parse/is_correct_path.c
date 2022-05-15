/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:23:17 by hnoh              #+#    #+#             */
/*   Updated: 2022/05/15 14:24:40 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	check_ls_result(int *ls_pipe, char *cmd)
{
	int		result;
	char	*line;
	char	**finded;
	char	**to_free;

	result = FALSE;
	while (get_next_line(ls_pipe[RD], &line) == SUCCESS)
	{
		finded = ft_split(line, ' ');
		to_free = finded;
		while (*finded)
		{
			if (!ft_strcmp(*finded, cmd))
			{
				result = TRUE;
				break ;
			}
			++finded;
		}
		free(line);
		free_char_ptr2d(to_free);
		if (result == TRUE)
			break ;
	}
	return (result);
}

int	is_correct_path(char *path, char *cmd)
{
	int		ls_pipe[2];
	int		pid;
	char	*ls_args[3];

	pipe(ls_pipe);
	pid = fork();
	if (pid == CHILD)
	{
		close(ls_pipe[RD]);
		dup2(ls_pipe[WR], STDOUT);
		ls_args[0] = "ls";
		ls_args[1] = path;
		ls_args[2] = NULL;
		execve("/bin/ls", ls_args, NULL);
		exit(0);
	}
	waitpid(CHILD, NULL, 0);
	close(ls_pipe[WR]);
	return (check_ls_result(ls_pipe, cmd));
}
