/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2022/04/08 12:38:02 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_status = 0;

int main(int argc, char *argv[], char *envp[])
{
	char *line;
	t_cmd_list *cmd_list;
	char **cpenv;
	if (!argv) return 0;

	dup2(STDIN, 100); // fd가 가리키는 기능을 변경하는 함수입니다. 표준입출력에 해당하는 fd를 100, 101에 백업합니다.
	dup2(STDOUT, 101);
	argc = 1;
	cpenv = copy_envp(envp);
	set_signal();
	while ((line = readline("minishell $ ")))
	{
		if (*line != '\0' && !check_whitespace(line)) // 프롬프트상에서 입력된 문자가 null이거나 모두 white_space일 때는 밑의 로직을 생략합니다.
		{
			add_history(line);
			parse(&cmd_list, line, cpenv); // 입력된 문자열을 먹기좋게 파싱합니다.

			// //print token
			// for (t_cmd *cmd = cmd_list; cmd; cmd = cmd->next)
			// {
			// 	for (t_token*token = cmd->cmdline;token->cmd;++token)
			// 		printf("token : %s %d\n", token->cmd, token->redir_flag);
			// 	printf("pipe %d  exit %d  right %d  quote %c\n",cmd->pipe_flag, cmd->exit_flag, cmd->right_flag, cmd->quote);
			// 	printf("\n");
			// }

			// g_exit_status = exec(cmd_list, argv, &cpenv); // 파싱된 명령어 및 문자열을 실행합니다.
			exec_arg(cmd_list, envp);
			printf("this\n");
			free_list(cmd_list);						  // 파싱된 데이터가 들어있는 list를 해제시켜줍니다.
			free(line);									  // readline으로 할당한 line을 해제시켜줍니다.
		}
	}
	ft_putstr_fd("\x1b[1A", STDOUT);
	ft_putstr_fd("\033[12C", STDOUT);
	ft_putstr_fd("exit\n", STDOUT);
	return (0);
}
