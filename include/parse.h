/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:34:41 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 13:25:15 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "utils.h"
# include "structs.h"

/* alloc_token */
int     alloc_env(char *src, char **dest, char **envp);
int     alloc_d_quote_cnt(char *src, char **dest, char **envp);
int	alloc_s_quote_cnt(char *src, char **dest);
void    cmd_copy(char *src, char *dest, char **envp);
t_token *alloc_token(t_token *token, char **envp);

/* alloc_word */
int     redir_len(char const **s, int *len);
int     count_word_len_on_flag(char const *s, int *len, int *flag);
int     word_len(char const *s);
char    *alloc_word(const char **s);

/* check */
int     check_whitespace(char *line);
int     check_redir(char *cmd);
int     check_unclosed_quote(char *str, char quote);

/*get env*/
char    *get_env_value(char *key, char **envp);
int     get_env_key(char *src, char **key);
int     get_env_key_size(char *str);
int	get_env_value_size(char *str, int size, char **envp);


/* get_parse_size */
int     get_parse_size(char *cmd, char **envp);

/* new_cmd */
t_cmd   *new_cmd(char *line, int pipe_flag, char **envp, int exit_flag);

/* parse */
int		is_correct_path(char *path, char *cmd);
char	*find_cmdpath(char *cmd, char **envp);
char	**read_cmd_arg(int fd);
void    parse(t_cmd **cmds, char *line, char **envp);

/* qoute_count */
char    *find_env(char *str, char **envp);
int     env_len(char *cmd, int *size, char **envp);
int     dquote_cnt(char *cmd, int *size, char **envp);
int     squote_cnt(char *cmd, int *size);

/* split_count */
void    masking_quote_flag(char const *s, int *flag);
void    count(int *flag, int *cnt, int make_begin_zero_flag);
void    count_on_flag(char const *s, int *flag, int *cnt);
int     split_count(char const *s);

/* split cmd */
void    *free_cmd(t_token *result, int len);
t_token *split_cmd(char const *s);

/* utils */
char    *cut_string(char **str);
char    **copy_envp(char **envp);
char    **sort_env(char **envp);
void    print_str_fd(char *s, int fd);







/* */
char    *get_env_value(char *key, char **envp);
int     get_env_key(char *src, char **key);

#endif
