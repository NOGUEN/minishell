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

# define BEGIN 0x00000001
# define SQUOTE 0x00000002
# define DQUOTE 0x00000004
# define REDIR 0x00000008
# define COUNT 0x000000016

/* signal */
void    signal_init(void);

/* check */
int     check_whitespace(char *line);

/* split_count */
void    maksing_quote_flag(char const *s, int *flag);
int     split_count(char const *s);
t_token *cmd_split(char const *s);
#endif