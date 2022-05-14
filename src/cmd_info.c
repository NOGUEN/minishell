/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:08:24 by soekim            #+#    #+#             */
/*   Updated: 2022/05/14 16:02:10 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cmd_info.h"

void	init_input(int *in_fd, t_token *in_redir, int (*pipes)[2])
{
	char	*hdoc_input;

	if (!ft_strcmp((in_redir - 1)->cmd, "<"))
		*in_fd = open_file(in_redir->cmd, O_RDONLY);
	else
	{
		*in_fd = pipes[P_TO_C][RD];
		if (!ft_strcmp((in_redir - 1)->cmd, "<<"))
		{
			while ((hdoc_input = readline("heredoc> ")))
			{
				if (!ft_strcmp(hdoc_input, in_redir->cmd))
					break ;
				ft_putendl_fd(hdoc_input, pipes[P_TO_C][WR]);
				free(hdoc_input);
			}
		}
		else if (!ft_strcmp((in_redir - 1)->cmd, "<<<"))
			ft_putstr_fd(in_redir->cmd, pipes[P_TO_C][WR]);
		else
		{
			printf("minishell: syntax error\n");
			g_exit_status = 258;
		}
	}
}

void	init_output(int *out_fd, char **out_name, t_token *out_redir)
{
	int	open_flag;

	open_flag = 0;
	if (!ft_strcmp((out_redir - 1)->cmd, ">"))
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else if (!ft_strcmp((out_redir - 1)->cmd, ">>"))
		open_flag = O_WRONLY | O_APPEND | O_CREAT;
	else
	{
		printf("minishell: parse error near '>'\n");
		g_exit_status = 258;
		return ;
	}
	*out_name = out_redir->cmd;
	*out_fd = open_file(*out_name, open_flag);
}

void	init_cmd_arg(t_cmd_info *info, t_token *token, int len_cmd_arg)
{
	int	i;
	int	cmd_i;

	info->cmd_args = malloc((len_cmd_arg + 1) * sizeof(char *));
	info->cmd_args[len_cmd_arg] = NULL;
	cmd_i = 0;
	if (token[0].cmd[0] != '<' && token[0].cmd[0] != '>')
	{
		info->cmd_args[0] = token[0].cmd;
		++cmd_i;
	}
	i = 1;
	while (token[i].cmd)
	{
		if (token[i].cmd[0] != '<' && token[i - 1].cmd[0] != '<'
			&& token[i].cmd[0] != '>' && token[i - 1].cmd[0] != '>')
		{
			info->cmd_args[cmd_i] = token[i].cmd;
			++cmd_i;
		}
		++i;
	}
}

void	init_cmd_info(t_cmd_info *info, t_token *tokens, int (*pipes)[2])
{
	int	len_cmd_arg;
	int	i;

	len_cmd_arg = 0;
	ft_memset(info, 0, sizeof(t_cmd_info));
	info->in_fd = NO_DATA;
	info->out_fd = NO_DATA;
	info->out_name = NULL;
	if (tokens[0].cmd[0] != '<' && tokens[0].cmd[0] != '>')
		++len_cmd_arg;
	i = 1;
	while (tokens[i - 1].cmd)
	{
		if (tokens[i - 1].cmd[0] == '<')
			init_input(&info->in_fd, &tokens[i], pipes);
		else if (tokens[i - 1].cmd[0] == '>')
			init_output(&info->out_fd, &info->out_name, &tokens[i]);
		else if (tokens[i].cmd && tokens[i].cmd[0] != '<'
			&& tokens[i].cmd[0] != '>')
			++len_cmd_arg;
		++i;
	}
	init_cmd_arg(info, tokens, len_cmd_arg);
}
