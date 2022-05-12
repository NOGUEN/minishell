/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:56:11 by noguen            #+#    #+#             */
/*   Updated: 2022/05/12 19:56:13 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    signal_sigint(int signo)
{
    pid_t   pid;
    int     status;

    pid = waitpid(-1, &status, WNOHANG);
    pid = pid * 1;
    if (signo == SIGINT)
    {
        if (pid == -1)
        {
            rl_on_new_line();
            rl_redisplay();
            print_str_fd("  \n", STDOUT);
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
        }
        else
            print_str_fd("\n", STDOUT);
    }
}

void    signal_sigquit(int signo)
{
    pid_t   pid;
    int     status;
    
    pid = waitpid(-1, &status, WNOHANG);
    pid = pid * 1;
    if (signo == SIGQUIT)
    {
        if (pid == -1)
        {
            rl_on_new_line();
            rl_redisplay();
            print_str_fd("  \b\b", STDOUT);
        }
        else
            print_str_fd("Quit: 3\n", STDOUT);
    }
}

void    signal_init(void)
{
    signal(SIGINT, signal_sigint);
    signal(SIGQUIT, signal_sigquit);
}
