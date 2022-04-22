#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct      s_token
{
    char            *cmd;
    char            redir_flag;
}                   t_token;

typedef struct      s_cmd_list
{
    t_token         *cmd_line;
    int             flag;
    char            *(redir_file[4]);
    struct s_cmd_list    *next;
}                   t_cmd;

#endif
