/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:08:24 by soekim            #+#    #+#             */
/*   Updated: 2022/04/02 12:23:01 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/inout.h"

void init_input(int *in_fd, t_token *in_redir, int (*pipes)[2])
{
	char *hdoc_input;

	if (!ft_strcmp((in_redir - 1)->cmd, "<"))
		*in_fd = open_file(in_redir->cmd, O_RDONLY);
	else 
	{
		*in_fd = pipes[PTOC][RD];
		if (!ft_strcmp((in_redir - 1)->cmd, "<<"))
		{
			while ((hdoc_input = readline("heredoc> ")))
			{
				//refactor to save heredocument input in .heredoc file
				if (!ft_strcmp(hdoc_input, in_redir->cmd))
					break;
				ft_putendl_fd(hdoc_input, pipes[PTOC][WR]);
				free(hdoc_input);
			}
		}
		else if (!ft_strcmp((in_redir - 1)->cmd, "<<<"))
			ft_putstr_fd(in_redir->cmd, pipes[PTOC][WR]);
		else
			error_exit("minishell: parse error near '<'\n");//should change from exit to goback to main loop
	}
}

void init_output(int *out_fd, char **out_name, t_token *out_redir)
{
	int open_flag;

	open_flag = 0;
	// printf("toekn %s|||||\n", out_redir->cmd);
	if (!ft_strcmp((out_redir - 1)->cmd, ">"))
	{
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
		// printf("flag\n");
	}
	else if (!ft_strcmp((out_redir - 1)->cmd, ">>"))
		open_flag = O_WRONLY | O_APPEND;
	else
		error_exit("minishell: parse error near '>'\n");
	*out_name = out_redir->cmd;
	*out_fd = open_file(*out_name, open_flag);
	// printf("opened:%d\n", *out_fd);
}

void init_cmd_arg(t_cmd_info *info, t_token *token, int len_cmd_arg)
{
	int i;
	int cmd_i;

	info->cmd_arg = malloc((len_cmd_arg + 1) * sizeof(char *));
	info->cmd_arg[len_cmd_arg] = NULL;
	cmd_i = 0;
	if (token[0].cmd[0] != '<' && token[0].cmd[0] != '>')
	{
		info->cmd_arg[0] = token[0].cmd;
		++cmd_i;
	}
	i = 1;
	while (token[i].cmd)
	{
		if (token[i].cmd[0] != '<' && token[i - 1].cmd[0] != '<' && token[i].cmd[0] != '>' && token[i - 1].cmd[0] != '>')
		{
			info->cmd_arg[cmd_i] = token[i].cmd;
			++cmd_i;
		}
		++i;
	}
}

void init_cmd_info(t_cmd_info *info, t_token *tokens, int (*pipes)[2])
{
	int len_cmd_arg;
	int i;
	len_cmd_arg = 0;
	ft_memset(info, 0, sizeof(t_cmd_info));
	info->in_fd = NO_DATA;
	info->out_fd = NO_DATA;
	info->out_name = NULL;
	if (tokens[0].cmd[0] != '<' && tokens[0].cmd[0] != '>')
		++len_cmd_arg;
	i = 1;
	while (tokens[i].cmd)
	{
		if (tokens[i - 1].cmd[0] == '<')
			init_input(&info->in_fd, &tokens[i], pipes);
		else if (tokens[i - 1].cmd[0] == '>')
			init_output(&info->out_fd, &info->out_name, &tokens[i]);
		else if (tokens[i].cmd[0] != '<' && tokens[i].cmd[0] != '>')
			++len_cmd_arg;
		++i;
	}
	init_cmd_arg(info, tokens, len_cmd_arg);
}