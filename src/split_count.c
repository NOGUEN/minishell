#include "../include/minishell.h"

void    count_redir(char const **s)
{
    char    tmp1;
    char    tmp2;

    tmp1 = **s;
    if (tmp1 == '<')
        tmp2 = '>';
    else
        tmp2 = '<';
    while (**s == tmp1 || **s == tmp2)
        (*s)++;
}

void    count_pipe(char const **s)
{
    char    tmp;

    tmp = **s;
    while (**s == tmp)
        (*s)++;
}

void    skip_space(char const **s)
{
    while (**s == ' ')
        (*s)++;
}

int split_count(char const *s, const char c)
{
    char    word_flag;
    int     cnt;
    char    quote;
    char    redir;

    cnt = 0;
    quote = 0;
    redir = 0;
    word_flag = 0;
    while (*s)
    {
        if (*s == '\"')
        {
            if (quote == '\"')
            {
                quote = 0;
                ++cnt;
            }
            else
                quote = '\"';
        }
        else if (*s == '\'')
        {
            if (quote == '\'')
            {
                quote = 0;
                ++cnt;
            }
            else
                quote = '\'';
        }
        else if (*s == '>' || *s == '<')
        {
            count_redir(&s);
            ++cnt;
        }
        else if (*s == '|')
        {
            count_pipe(&s);
            ++cnt;
        }
        else if (*s == ' ')
        {
            if (word_flag == 1)
            {
                word_flag = 0;
                ++cnt;
            }
            skip_space(&s);
        }
        else
            word_flag = 1;
        ++s;
    }
    if (quote != 0 || word_flag == 1)
        ++cnt;
    return (cnt);
}