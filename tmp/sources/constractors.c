#include "../includes/minishell.h"

char **new_str(char **old_str)
{
    int i, old_len;
    char **res;

    i = 0;
    old_len = dstr_len(old_str);
    res = (char **)malloc(sizeof(char *) * (old_len + 2));
    if (NULL == res)
        return (NULL);
    if (old_str)
    {
        while (i < old_len)
        {
            res[i] = ft_strdup(old_str[i]);
            i++;
        }
    }
    res[i] = NULL;
    free_mynigga(old_str);
    return (res);
}

t_cmd *init_pipe(t_cmd *left, t_cmd *right)
{
    struct pipe *res;

    res = malloc(sizeof(*res));
    if (!res)
        panic("init_pipe\n");
    res->type = PIPE;
    res->pipe_fd = -1;
    res->left = left;
    res->right = right;
    return ((t_cmd *)res);
}

// void herdoc_content(t_cmd *herd)
// {
//     struct heredoc *p;
//     char *str;
//     int i;

//     i = 0;
//     p = (struct heredoc *)herd;
//     p->content = NULL;
//     str = readline(">");
//     while(ft_strcmp(str, p->delimiter) == 0)
//     {
       
//         p->content = new_str(p->content);
//         p->content[i] = ft_strdup(str);
//         //  printf("ALO\n");
//         free(str);
//         i++;
//         p->content[i] = NULL;
//         str = readline(">");
//     }
// }

// t_cmd *init_new_cmd(char *argv, char **env, t_red *redirect)
// {
//     struct new_cmd *res;

//     res = malloc(sizeof(*res));
//     if (NULL == res)
//         return (NULL);
//     res->type = NEW_CMD;
//     res->argv = argv;
//     res->env = env;
//     res->fd_in = 0;
//     res->fd_out = 1;
//     res->redirect = redirect;
//     return ((t_cmd *)res);
// }

t_cmd *init_new_cmd(char **argv, t_env *myenv,t_red *redirect, t_herdoc *herdoc1)
{
    struct new_cmd *res;

    res = malloc(sizeof(*res));
    if (NULL == res)
        return (NULL);
    res->type = NEW_CMD;
    res->argv = argv;
    res->myenv = myenv;
    res->fd_in = -1;
    res->fd_out = -1;
    res->redirect = redirect;
    res->last_pipe_cmd = -1;
    // res->herdoc_pipe = herdoc_pipe;
    res->herdoc = herdoc1;
    return ((t_cmd *)res);
}

t_red *creat_red_lst(char **tokens, int i)
{
    t_red *res;

    res = (t_red *)malloc(sizeof (t_red ));
    if (!res)
        return (NULL);
    res->type = get_type(tokens, i);
    res->mode = get_mode(tokens, i);
    if (res->mode == 4 || res->type == HERDOC)
        res->fd = 0;
    else
        res->fd = 1;
    i++;
    res->file = ft_strdup(tokens[i]);
    res->next = NULL;
    return res;
}

void add_to_lst(t_red *red_lst, char **tokens, int i)
{
    t_red *new_red;
    t_red *tmp;


    new_red = NULL;
    tmp = red_lst;
    new_red = creat_red_lst(tokens, i);
    if (NULL == new_red)
        return;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_red;
}



// int main (int ac, char **av)
// {
//    char **s = NULL;
//    printf("%d\n", dstr_len(s));
// }