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
#include "structs.h"
#include "../libft/libft.h"

# define BEGIN 0x00000001
# define SQUOTE 0x00000002
# define DQUOTE 0x00000004
# define REDIR 0x00000008
# define COUNT 0x000000016

/* signal */
void    signal_sigint(int signo);
void    signal_sigquit(int signo);
void    signal_init(void);

/* check */
int     check_whitespace(char *line);

/* split_count */
void    masking_quote_flag(char const *s, int *flag);
void    count(int *flag, int *cnt, int make_begin_zero_flag);
void    count_on_flag(char const *s, int *flag, int *cnt);
int     split_count(char const *s);

void    *free_cmd(t_token *result, int len);
t_token *split_cmd(char const *s);

/* */
int     redir_len(char const **s, int *len);
int     count_word_len_on_flag(char const *s, int *len, int flag);
int     word_len(char const *s);
char    *alloc_word(const char **s);

/* */
int     get_parse_size(char *cmd, char **envp);

/* */
t_token *alloc_token(t_token *token, char **envp);

/* */
int     env_len(char *str, char **envp);

/* */
char    *find_env(char *str, char **envp);
int     env_len(char *str, char **envp);
int     dquote_cnt(char **cmd, char **envp);
int     squote_cnt(char **cmd);


/* */
t_cmd   *new_cmd(char *line, int pipe_flag, char **envp, int exit_flag);

/* utils */
char    *cut_string(char **str);
#endif