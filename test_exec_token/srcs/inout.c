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

// void	init_inout(t_inout *inout, t_arg *arg)
//{
//	ft_memset(inout, sizeof(t_inout), 0);
//	inout->in.o_flag = O_RDONLY;
//	inout->in.fd = open_file(arg->vec[1], inout->in.o_flag);
//	inout->out.o_flag = O_RDWR | O_CREAT | O_TRUNC;
//	if (arg->cnt > 4)
//		inout->out.fd = open_file(arg->vec[arg->cnt - 1], inout->out.o_flag);
//	else
//		inout->out.fd = STDOUT;
//	return ;
// }

// init in_out file of each command in one pipe
//  void	init_inout(t_inout *inout, t_cmd *cmd)
//  {
//  	ft_memset(inout, sizeof(t_inout), 0);
//  	inout->in.o_flag = O_RDONLY;
//  	inout->in.fd = open_file(cmd->redir_file[0], inout->in.o_flag);
//  	inout->out.o_flag = O_RDWR | O_CREAT | O_TRUNC;
//  	if (arg->cnt > 4)
//  		inout->out.fd = open_file(arg->vec[arg->cnt - 1], inout->out.o_flag);
//  	else
//  		inout->out.fd = STDOUT;
//  	return ;
//  }

void init_input(int *input, t_token *in_redir)
{
	if (!ft_strcmp(in_redir[0].cmd, "<"))
		*input = open_file(in_redir[1].cmd, O_RDONLY);
	// else if (!ft_strcmp(in_redir->cmd, "<<"))
	// 	;
	// implement stdin until in_redir[1].cmd comes in
	else
		exit(0);
	// error
}

void init_output(int *output, t_token *out_redir)
{
	int open_flag;

	if (!ft_strcmp(out_redir[0].cmd, ">"))
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	// else if (!ft_strcmp(out_redir->cmd, ">>"))
	// 	open_flag = O_WRONLY | O_APPEND;
	else
		open_flag = O_WRONLY | O_APPEND;
	// should change to error

	*output = open_file(out_redir[1].cmd, open_flag);
}

void init_cmd_arg(t_token_info *info, t_token *token, int len_cmd_arg)
{
	int i;
	int cmd_i;

	info->cmd_arg = malloc((len_cmd_arg + 1) * sizeof(char *));
	info->cmd_arg[len_cmd_arg] = NULL;
	//	consider <<< (here string)
	cmd_i = 0;
	if (token[0].cmd[0] != '<' && token[0].cmd[0] != '>')
	{
		info->cmd_arg[0] = token[0].cmd;
		++cmd_i;
	}
	i = 1;
	while (token[i].cmd)
	{
		if (token[i - 1].cmd[0] != '<' && token[i - 1].cmd[0] != '>')
		{
			info->cmd_arg[cmd_i] = token[i].cmd;
			++cmd_i;
		}
		++i;
	}
}

void init_token_info(t_token_info *info, t_token *token)
{
	int len_cmd_arg;
	int i;
	// consider <<< (here string)
	len_cmd_arg = 0;
	ft_memset(info, 0, sizeof(t_token_info));
	info->input = NO_DATA;
	info->output = NO_DATA;
	if (token[0].cmd[0] != '<' && token[0].cmd[0] != '>')
		++len_cmd_arg;
	i = 1;
	while (token[i].cmd)
	{
		if (token[i - 1].cmd[0] == '<')
			init_input(&info->input, &token[i]);
		else if (token[i - 1].cmd[0] == '>')
			init_output(&info->output, &token[i]);
		else if (token[i].cmd[0] != '<' && token[i].cmd[0] != '>') 
			++len_cmd_arg;
		++i;
	}
	init_cmd_arg(info, token, len_cmd_arg);
}