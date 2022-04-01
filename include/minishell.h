#ifndef MINISHELL_H
#define MINISHELL_H

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "libft/libft.h"

#define PIPE    0000000001
#define EXIT    0000000010
#define RIGHT   0000000100
#define REDIR   0000001000

/* signal */
void    signal_init(void);

/* check */
int     check_whitespace(char *line);

#endif