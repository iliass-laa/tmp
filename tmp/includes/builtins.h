#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"


void execute_cmd(t_cmd *cmd);
int exec_builtin(t_cmd *cmd);
bool is_builtin(t_cmd *cmd);

/*   ECHO   */
/*  CD  */
int cd(t_cmd *cmd);

/*  PWD */
int pwd(t_cmd *cmd);

/*  ENV  */
t_env *init_env(char **env_main);
t_env *creat_env(char *pair);
void add_back_env(t_env **head, t_env*node);
void print_env(t_env *env);

/*  EXPORT  */
void export(t_env *ennv,char *cmd_args);
void print_export(t_env *env);
char *clean_arg(char *arg);

/*  UNSET   */
void destroy_single_env(t_env *node);
void unset_env(t_env **head, char *key);


/*   EXIT   */

/*  UTILS   */

char **lstoarry(t_env *root);



// void penv(t_env *env);

# endif 