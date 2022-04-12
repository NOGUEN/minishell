/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 22:37:02 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 20:42:46 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int check_ls_result(int *ls_pipe, char *cmd)
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
				break;
			}
			++finded;
		}
		free(line);
		free_char_ptr2d(to_free);
		if (result == TRUE)
			break;
	}
	return result;
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
	return check_ls_result(ls_pipe, cmd);
}

char	**get_path_list(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!strdelcpy("PATH", envp[i], '='))
			break ;
		++i;
	}
	return (ft_split(envp[i] + 5, ':'));
}

char	*find_cmdpath(char *cmd, char **envp)
{
	char	**path_list;
	char	**to_free;
	char	*to_cat;
	char	*path;

	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3))
		return (*ft_split(cmd, ' '));
	path_list = get_path_list(envp);
	to_free = path_list;
	while (*path_list)
	{
		if (is_correct_path(*path_list, cmd))
			break ;
		++path_list;
	}
	if (!(*path_list))
		cmd_not_found(cmd);
	to_cat = ft_strjoin("/", cmd);
	path = ft_strjoin(*path_list, to_cat);
	free(to_cat);
	free_char_ptr2d(to_free);
	return (path);
}
