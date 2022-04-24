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
#include "../includes/minishell.h"

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

	if (!cmd || !*cmd)
		error_exit("command didn't pass to find path\n");
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


void			parse(t_cmd **cmd_list, char *line, char **envp)
{
	int			i;
	int			start;
	int			pipe_flag;
	t_cmd		*tmp;
	t_cmd		*new;
	int			quote_flag;

	quote_flag = 0;
	i = 0;
	start = 0;
	pipe_flag = 1;
	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
	{
		if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 0) //파이프가 따옴표 안에 들어가는 경우 끊으면 안됨.
            quote_flag = 1;
        else if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 1)
            quote_flag = 0;
		if (line[i] == '\0' || (line[i] == '|' && quote_flag == 0)) // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
		{
			if (line[i] == '|')
				line[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
			else
				pipe_flag = 0;
			if ((new = ft_new(&line[start], pipe_flag, envp, start)) == 0)
				return ;
			if (start == 0)
			{
				*cmd_list = new;
				tmp = *cmd_list;
			}
			else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
			{
				(*cmd_list)->next = new;
				*cmd_list = (*cmd_list)->next;
			}
			if (pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
				break ;
			start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		i++;
	}
	*cmd_list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
}
