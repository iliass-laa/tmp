#include "../includes/minishell.h"

void ft_swap_str(char **s1,char **s2)
{
    char *tmp;

    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}


char *join_cmd(char *s1, char *s2)
{
    int i;
    int reslen;
    char *res;

    reslen = ft_strlen(s1) + ft_strlen(s2);
    if(NULL != s1)
        reslen += 1;
    res = (char *)malloc(reslen + 1);
    int l= ft_strlen(s1);
    i = 0;
    while(i < l)
    {
        res[i] = s1[i];
        i++;
    }
    if (l > 0)
        res[i] = 32;
    i++;
    l = 0;
    while ((size_t)l < ft_strlen(s2))
        res[i++] = s2[l++];
    res[i] = 0;
    free(s1);
    return (res);
    
}

char *cmd_line(char **tokens, int *x)
{
    int i, j;
    t_typenode ref;
    char *cmd;

    i = *x;
    ref = EXEC;
    cmd = NULL;
    while (tokens[i])
    {
        j = which_one(tokens[i]);
        if (PIPE == j)
            break;
        if (ref == RED || ref == HERDOC )
           { ref = FILE_NAME;}
        else if (FILE_NAME == ref)
           { ref = EXEC;}
        if (j == RED || j == HERDOC)
          {  ref = j;}
        if (ref == EXEC)
        {
            if (NULL == cmd)
                cmd = ft_strdup(tokens[i]);
            else
                cmd = join_cmd(cmd , tokens[i]);
        }
        i++;
    }
    *x = i;
    return(cmd);
}

int get_mode(char **tokens, int i)
{
    if (ft_strcmp(tokens[i], "<"))
        return (4);
    if (ft_strcmp(tokens[i], ">>"))
        return(77);
    if (ft_strcmp(tokens[i], ">"))
        return(7);
    return (0);
}

int get_type(char **tokens, int i)
{
    if (ft_strcmp(tokens[i], "<<"))
        return (HERDOC);
    return (RED);
}

void do_nothing(int signal)
{
    printf("\n>\n");
    return;
}


// int get_content(char *del, int *heredoc_pipe)
// {
//      char *str;
//     int p[2];
//     int pid;
//     int pid_status, status;
//     // struct sigaction sa_old, sa_ignore;
//     // sa_ignore.sa_handler = SIG_IGN;
//     // sigaction(SIGINT, &sa_ignore, &sa_old);
//     if (*heredoc_pipe != -1)
//     {
//         dprintf(2,"closing this pipe:%d\n", *heredoc_pipe);
//         close(*heredoc_pipe);
//     }
//     pipe(p);
//     pid = fork();
//     if(0 == pid)
//     {
//         signal(SIGINT, NULL);
//         while(1)
//         {
//             str = readline(">");
//             if (ft_strcmp(str, del))
//                 break;
//             ft_putstr_fd(str, p[1]);
//             ft_putstr_fd("\n", p[1]);
//         }
//         close(p[1]);
//         close(p[0]);
//         exit(0);
//     }
//     else if (pid > 0)
//     {
//         signal(SIGINT, do_nothing);
//         pid_status =  waitpid(pid, &status,0);
//         signal(SIGINT, signal_handler);
//         if (WTERMSIG(status)  == SIGINT)
//             sig = -99;
//         if (pid_status != -1)
//             *heredoc_pipe = p[0];
//         else
//             close(p[0]);
//         close(p[1]);
//     }
//     return (p[0]);
// }

void assign_her_exp(t_del *lst, t_herdoc *herdoc)
{
    t_del *tmp;

    tmp = lst;
    if (!tmp)
        return ;
    while (tmp-> next)
    {
        tmp = tmp->next;
    }
    herdoc->to_exp = tmp->to_exp;
}

void herdoc_treat(t_del *lst, t_herdoc *herdoc)
{   
    int pid, status;
    int p[2];
    char *str;

    if (NULL == lst)
        return;
    pipe(p);
    pid = fork();
    if (pid == 0)
    {
        signal (SIGINT, NULL);
        while (lst != NULL)
        {
            while (1)
            {
                str = readline(">");
                if (ft_strcmp(str, lst->del))
                    break;
                if (lst->next == NULL)
                {
                    ft_putstr_fd(str, p[1]);
                    ft_putstr_fd("\n", p[1]);
                }
            }
            lst =lst->next;
        }
        close(p[1]);
        close(p[0]);
        exit(0);
    }
    else if(pid > 0)
    {
        signal(SIGINT, do_nothing);
        waitpid(pid, &status,  0);
        signal(SIGINT, signal_handler);
        if (WTERMSIG(status)  == SIGINT)
            sig = -99;
        if (sig == -1)
            herdoc->herdoc_pipe = p[0];
        else
            close (p[0]);
        close(p[1]);
    }
}

void get_herdoc(char **tokens,int i, t_herdoc *herdoc)
{
    t_del *str;
    char *delimiter;
    
    str = NULL;
    while (tokens[i] && PIPE != which_one(tokens[i]))
    {
        if (which_one(tokens[i]) == HERDOC)
        {
            i++;
            delimiter = ft_strdup(tokens[i]);
            if (NULL == str)
                str = first_del(str, delimiter);
            else
                str = add(str, delimiter);
            i--;
        }
        i++;
    }
    assign_her_exp(str, herdoc);
    if (sig == -1)
        herdoc_treat(str, herdoc);
    return;
}

t_red *get_red(char **tokens, int i, t_herdoc *herdoc)
{
    t_red *red_lst;

    red_lst = NULL;
    while (tokens[i] && PIPE != which_one(tokens[i]))
    {
        if (which_one(tokens[i]) == RED || HERDOC == which_one(tokens[i]))
        {
            if (NULL == red_lst)
                red_lst = creat_red_lst(tokens, i);
            else
                add_to_lst(red_lst, tokens, i);
            if (!red_lst)
                return(NULL);
            i++; 
        }
        i++;
    }
    return (red_lst);
}

