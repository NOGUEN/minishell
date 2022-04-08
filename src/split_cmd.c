#include "../include/minishell.h"

int word_length(char const *s)
{
    int     len;
    char    quote;

    len = 0;
    quote = 0;
    while (*s)
    {
        if (*s == '\"')
        {
            if (quote == '\"')
                quote = 0;
            else
                quote = '\"';
            ++s;
        }
        else if (*s == '\'')
        {
            if (quote == '\'')
                quote = 0;
            else
                quote = '\'';
            ++s;
        }
        else if (*s == '>' || *s == '<')
        {
            while (*s == '>' || *s == '<')
            {
                ++len;
                ++s;
            }
        }
        else if (*s == ' ')
            return (len);
        ++len;
        ++s;
    }
    return (len);
}

char    *word_alloc(char const **s)
{
    int     i;
    int     word_len;
    char    *word;


    word_len = word_length(*s);
    word = malloc(sizeof(char) * (word_len + 1));
    if (word == NULL)
        return (NULL);
    i = -1;
    while (++i < word_len)
        word[i] = *((*s)++);
    word[i] = '\0';
    return (word);
}

t_token *cmd_split(char const *s)
{
    int     result_index;
    t_token *result;

    result = malloc(sizeof(t_token) * (split_count(s) + 1));
    if (result == NULL)
        return (NULL);
    result_index = 0;
    while (*s)
    {
        if (*s == ' ')
            ++s;
        else
        {
            result[result_index].cmd = word_alloc(&s);
            result[result_index].redir_flag = 0;
            ++result_index;
        }
    }
    result[result_index].cmd = 0;
    return (result);
}