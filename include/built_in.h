#ifndef BUILT_IN_H
# define BUILT_IN_H

# define CD_FAILED -1

# include "../libft/libft.h"
# include "vars.h"
# include "utils.h"


/* export */
void    print_export(char **envp);
void    export_new(t_cmd_info *cmd_info, char ***envp);
void    update_existing_count_new(t_cmd_info *cmd_info, char ***envp, int *pcount);
void    update_existing(char **existing, char *new_val);
/* export utils */
int     is_valid_key(char *key);
int     is_valid_export(char *line);
char    **find_existing_var(char *token, char **envp);

/* cd */
void    cd(t_cmd_info *cmd_info, int (*pipes)[2], int *input);

/* unset */
void    unset(t_cmd_info *cmd_info, char ***envp);

/* env */
void    env(char **envp);

/* exit */
void    ft_exit(char **args);

#endif