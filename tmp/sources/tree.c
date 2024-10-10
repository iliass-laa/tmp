#include "../includes/minishell.h"

int is_pipe(char *s)
{
    if (ft_strlen(s) == 1 && s[0] == '|')
        return(1);
    return(0);
}

// t_cmd *parse_exec(char **tokens, int *i, char **env)
// {
//     t_cmd *res;
//     struct exec_cmd *p;
//     char *argv;

//     res = NULL;
//     if (RED == which_one(tokens[*i]))
//         return NULL;
//     argv = ft_strdup(tokens[*i]);
//     p = (struct exec_cmd *)init_exec(EXEC,argv, env);
//     res = (t_cmd *)p;
//     (*i)++;
//     return(res);
// }

// t_cmd *parse_redirect(char **tokens, int *i, char **env)
// {
//     t_cmd *res;
//     int fd;
//     int mode;
//     char *file;

//     res = NULL;
//     fd = 1;
//     // write(1, "al\n", 4);
//     // if (tokens[*i] && (which_one(tokens[*i]) != RED))
//     res = parse_exec(tokens, i, env);
//     while (tokens[*i] && (which_one(tokens[*i]) == RED))
//     {
//         if ( 1 == ft_strcmp(tokens[*i], ">>"))
//             mode = 77;
//         else if (ft_strcmp(tokens[*i], ">"))
//             mode = 7;
//         else if (ft_strcmp(tokens[*i], "<"))
//         {
//             mode = 4;
//             fd = 0;
//         }
//         (*i)++;
//         file = ft_strdup(tokens[*i]);
//         (*i)++;
//         res = init_redire(res, file, mode, fd);
//     }
//     return (res);
// }

struct cmd *parse_pipe(char **tokens, int *i, t_env *myenv)
{
    t_cmd *res;

    res = parse_new_exec(tokens, i, myenv);
    if  (tokens[*i] && is_pipe(tokens[*i]))
    {
        (*i)++;
        res = (t_cmd *)init_pipe(res, parse_pipe(tokens , i, myenv));
    }
    // printf("cmd is parsed\n");
    return (res);
    
}

t_cmd *parse_new_exec(char **tokens, int *i, t_env *env)
{
    t_cmd *res;
    t_red *redirect;
    t_herdoc *herdoc;
    char *argv;
    char **argv1;
    int x;
    int heredoc_pipe;

    res = NULL;
    x = *i;
    herdoc = (t_herdoc *)malloc(sizeof (*herdoc));
    if (!herdoc)
        panic("malloc failed\n");
    herdoc->herdoc_pipe = -1;
    herdoc->to_exp = 0;
    get_herdoc(tokens, *i, herdoc);
    argv = cmd_line(tokens, i);
    argv1 = fr9_trb7(argv);
    free(argv);
    redirect = get_red(tokens, x, herdoc);
    res = (t_cmd *)init_new_cmd(argv1, env, redirect, herdoc);
    return(res);
}

t_cmd *root(char **tokens, t_env *env)
{
    int i = 0;
    t_cmd *res;
    // struct pipe *p;
    // struct new_cmd *cmd;

    res = NULL;
    res = parse_pipe(tokens, &i, env);
    // if (res->type == PIPE)
    // {
    //     // p = (struct pipe *)res;
    //     // cmd = (struct new_cmd *)p->right;
    //     // printf("root heredoc pipe cmd :%d\n", cmd->);
    //     // printf("root type cmd :%d\n", cmd->type);
    //     // printf("root left cmd :%s\n", cmd->argv);
    //     // printf("root cmd :%d\n", p->left->type);
    //     // printf("root cmd :%d\n", res->type);
    // }
    return(res);
}