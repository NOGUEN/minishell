#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct      s_token
{
    char            *cmd;
    char            redir_flag;
}                   t_token;

typedef struct      s_cmd_list
{
    t_token         *tokens;
    int             flag;
    char            *(redir_file[4]);
    int             pipe_flag;
    int             exit_flag;
    struct s_cmd_list    *next;
}                   t_cmd;

#endif
