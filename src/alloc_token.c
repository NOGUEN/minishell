#include "../include/minishell.h"

char    *get_env_value(char *key, char **envp)
{
    int i;

    i = -1;
    while (envp[++i])
    {
        if (!ft_strncmp(key, envp[i], ft_strlen(key)) 
                && envp[i][ft_strlen(key)] == '=')
            return (envp[i] + ft_strlen(key) + 1);
    }
    return (NULL);
}

int get_env_key(char *src, char **key)
{
    int     key_len;

    printf("env_key : %s\n", src);
    src++;
    *key = cut_string(&src);
    key_len = ft_strlen(*key) + 1;
    return (key_len);
}

void    alloc_env(char *src, char **dest, char **envp, int *index)
{
    char    *status;
    char    *key;
    char    *env_val;
    int     env_len;

    if (src[1] == '?')
    {
        status = ft_itoa(g_exit_status);
        ft_memcpy(*dest, status, ft_strlen(status));
        *dest += ft_strlen(status);
        free(status);
        (*index)++;
        return ;
    }
    else if (src[1] == '\0' || src[1] == '\"')
    {
        **dest = '$';
        *dest += 1;
        return ;
    }
    key = NULL;
    *index += get_env_key(src, &key);
    printf("%d\n", *index);
    printf("%s\n", key);
    env_val = get_env_value(key, envp);
    printf("env_val : %s", env_val);
    env_len = ft_strlen(env_val);
    ft_memcpy(*dest, env_val, env_len);
    *dest += env_len;
    free(key);
}

void    alloc_d_quote_cnt(char *src, char **dest, char **envp, int *index)
{
    (*index)++;
    while (src[*index] && src[*index] != '\"')
    {
        if (src[*index] == '$')
            alloc_env(&src[*index], dest, envp, index);
        else
        {
            printf("word : %c\n", src[*index]);
            printf("index : %d\n", *index);
            **dest = src[*index];
            (*dest)++;
            (*index)++;
        }
    }
}

void    alloc_s_quote_cnt(char *src, char **dest, int *index)
{
    int src_index;
    int dest_length;

    src_index = 0;
    dest_length = 0;
    while (src[++src_index] && src[src_index] != '\'')
        dest_length++;
    ft_memcpy(*dest, src + 1, dest_length);
    *dest += dest_length;
    *index += src_index;
}

void    cmd_copy(char *src, char *dest, char **envp)
{
    int src_index;
    char *dest_end;

    src_index = -1;
    dest_end = dest;
    while (src[++src_index])
    {
        if (src[src_index] == '\'' && check_unclosed_quote(&src[src_index], '\''))
            alloc_s_quote_cnt(&src[src_index], &dest_end, &src_index);
        else if (src[src_index] == '\"' && check_unclosed_quote(&src[src_index], '\"'))
            alloc_d_quote_cnt(&src[src_index], &dest_end, envp, &src_index);
        else if (src[src_index] == '$')
            alloc_env(&src[src_index], &dest_end, envp, &src_index);
        else if (src[src_index])
        {
            *dest_end = src[src_index];
            dest_end++;
        }
    }
    *dest_end = '\0';
}

t_token *alloc_token(t_token *token, char **envp)
{
    int cmd_len;
    size_t  i;
    char *tmp_cmd;

    i = 0;
    while (token[i].cmd)
    {
        cmd_len = 0;
        tmp_cmd = token[i].cmd;
        printf("tmp_cmd : %s\n", tmp_cmd);
        cmd_len = get_parse_size(tmp_cmd, envp);
        printf("cmd_len : %d\n", cmd_len);
        if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>')
        {
            if (check_redir(token[i].cmd))
                token[i].redir_flag = 1;
            else
                token[i].redir_flag = -1;
        }
        if (cmd_len != 0)
        {
            token[i].cmd = (char *)malloc(sizeof(char) * (cmd_len + 1));
            cmd_copy(tmp_cmd, token[i].cmd, envp);
        }
        printf("token : %s\n", token[i].cmd);
        i++;
    }
    return (token);
}