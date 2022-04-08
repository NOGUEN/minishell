#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct      s_token
{
    char            *cmd;
    char            redir_flag;
}                   t_token;

typedef struct      s_cmd
{
    t_token         *cmds;
    int             flag;
    char            *(redir_file[4]);
    struct s_cmd    *next;
}                   t_cmd;

#endif
