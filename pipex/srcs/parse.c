/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 22:37:02 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 13:27:39 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	is_correct_path(char *path, char *cmd)
{
	int		pid;
	int		ls_pipe[2];
	char	*line;
	char	**paths;

	pipe(ls_pipe);
	pid = fork();
	if (pid == CHILD)
	{
		close(ls_pipe[RD]);
		char *args[2];
		args[0] = "ls";
		args[1] = NULL;
		execve("/bin/ls", args, NULL);
	}
	waitpid(CHILD, NULL, 0);
	close(ls_pipe[WR]);
	while (get_next_line(ls_pipe[RD], &line) == SUCCESS)
	{
		line
	}
	return 0;
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
	char	**to_find;
	char	*to_cat;
	char	*path;

	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3))
		return (*ft_split(cmd, ' '));
	to_find = ft_split(cmd, ' ');
	path_list = get_path_list(envp);
	to_free = path_list;
	while (*path_list)
	{
		if (is_correct_path(*path_list, *to_find))
			break ;
		++path_list;
	}
	if (!(*path_list))
		cmd_not_found(*to_find);
	to_cat = ft_strjoin("/", *to_find);
	path = ft_strjoin(*path_list, to_cat);
	free(to_cat);
	free_char_ptr2d(to_find);
	free_char_ptr2d(to_free);
	return (path);
}
