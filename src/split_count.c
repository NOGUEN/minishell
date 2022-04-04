#include "../include/minishell.h"

int split_count(char const *s)
{
    char    word_flag;
    int     cnt;
    char    quote;

    cnt = 0;
    quote = 0;
    word_flag = 0;
    while (*s)
    {
        if (*s == '\"')
        {
            if (quote == '\"')
            {
                quote = 0;
                if (word_flag == 0)
                    ++cnt;
            }
            else
                quote = '\"';
            ++s;
        }
        else if (*s == '\'')
        {
            if (quote == '\'')
            {
                quote = 0;
                if (word_flag == 0)
                    ++cnt;
            }
            else
                quote = '\'';
            ++s;
        }
        else if (*s == '>' || *s == '<')
        {
            if (word_flag == 1)
                ++cnt;
            while (*s == '>' || *s == '<')
                ++s;
            ++cnt;
        }
        else if (*s == ' ')
        {
            if (word_flag == 1)
            {
                word_flag = 0;
                ++cnt;
            }
            while (*s == ' ')
                ++s;
        }
        else
        {
            word_flag = 1;
            ++s;
        }
    }
    if (quote != 0 || word_flag == 1)
        ++cnt;
    return (cnt);
}