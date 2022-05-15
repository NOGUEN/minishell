/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmdpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:05:29 by hnoh              #+#    #+#             */
/*   Updated: 2022/05/15 14:12:08 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

char	**get_path_list(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!strdelcmp("PATH", envp[i], '='))
			break ;
		++i;
	}
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*find_cmdpath_split(char *cmd, char **envp)
{
	char	**path_list;
	char	**to_free;
	char	*to_cat;
	char	*path;

	path_list = get_path_list(envp);
	if (!path_list)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		exit(127);
	}
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

char	*find_cmdpath(char *cmd, char **envp)
{
	if (!cmd || !*cmd)
		error_exit("command didn't pass to find path\n");
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3))
		return (*ft_split(cmd, ' '));
	if (cmd[0] == '/')
	{
		if (is_correct_path(cmd, cmd))
			return (cmd);
		else
			cmd_not_found(cmd);
	}
	return (find_cmdpath_split(cmd, envp));
}
