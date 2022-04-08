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
#include "../libft/libft.h"
#include "structs.h"

/* signal */
void    signal_init(void);

/* check */
int     check_whitespace(char *line);

/* split */
int     split_count(char const *s);
t_token *cmd_split(char const *s);
#endif