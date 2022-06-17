/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:57:56 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 19:12:52 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

void    checksignal(int nbr)
{
    if (nbr == SIGINT)
        exit(1);
}

int finde_her(t_list *lis)
{
    while (lis)
    {
        if (lis->v_type[0] == 11)
            return 1;
        lis = lis->next;  
    }
    return  0;
}

int     finder_red(t_list *list)
{
    while (list)
    {
        if (list && (list->v_type[0] == 6 || list->v_type[0] == 4))
            return 2;
        else if (list && list->v_type[0] == 8)
            return 3;
        else if (list && list->v_type[0] == 3)
            return 4;
        list = list->next;
    }
    return 0;
}

// void	handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		status_exec_g = 130;
// 	}
// 	if (sig == SIGQUIT)
// 	{
// 		rl_redisplay();
// 	}
// }

void    ft_mini(t_shell *mini, char *src)
{
    t_list *lst;
    t_list *head;
    int     i;
    lst = ft_parser(src, mini);
    
//         i = 0;
    // head = lst;
        // head = lst;
    while (lst)
    {
        i = 0;
        while (lst->val[i])
        {
            printf("%s -- %d" , lst->val[i], lst->v_type[i]);
            free(lst->val[i]);
            i++;
        }
        // free(lst->v_type);
        printf("\n");
            lst = lst->next;
    }
    free(lst);
    
//     // // head = lst;
// >>>>>>> aa56db1cb89061811f73e84e704e5c791f795549
    
    //             printf("list [%d] = %s", i++, lst->val[0]);
    // while (lst)
    // {
    //     // printf("%s -- " , lst->val[0]);
    //     // while (lst->val[i])
    //     // {
    //         if(lst->prev)
    //         {
    //             printf("prev [%d] = %s", i ,lst->prev->val[0]);
    //         printf("\n");
    //             printf("list [%d] = %s", i++, lst->val[0]);

    //         }
    //     // }
    //         // printf("%s | " , lst->val[i++]);
    //     printf("\n");
    //         lst = lst->next;
    // }

<<<<<<< HEAD
    // lst = head;
    if (!lst)
        return;
    else if (finde_her(lst) == 1)
        pipes(mini, lst);
    else if (finder_red(lst) == 2)
       ft_redirection(mini, lst, 0, 1);
    else if (finder_red(lst) == 4)
        heredoc(mini, lst, 0, 1);
    else if (finder_red(lst) == 3)
        ft_redin(mini, lst, 1, 0);
    else
    {
        ft_exit_status(mini, lst);
        ft_check_built(mini, lst, 1);
    }
=======
    //lst = head;
    // if (!lst)
    //     return;
    // else if (finde_her(lst) == 1)
    //     pipes(mini, lst);
    // else if (finder_red(lst) == 2)
    //    ft_redirection(mini, lst, 0, 1);
    // else if (finder_red(lst) == 4)
    //     heredoc(mini, lst, 0, 1);
    // else if (finder_red(lst) == 3)
    //     ft_redin(mini, lst, 1, 0);
    // else
    // {
    //     ft_exit_status(mini, lst);
    //     ft_check_built(mini, lst, 1);
    // }
    system("leaks minishell");
>>>>>>> e2cb4795bfc8a709b566da8d333f9a0a453e23ff
}

int main(int ac, char **av, char **env)
{
    char    *src;
    t_shell mini;

   (void)ac;
   (void)av;
    mini.tab_save_env = env;
    mini.tab_save_exp = NULL;
    mini.counter = 0;
    mini.num_ofall_cmd = 0;
    mini.num_cmd = 0;
    mini.cnt = 0;
    mini.fs = 0;
    //signal(SIGINT, handler);
    while(1337)
    {
        //printf("errno = %d\n", errno);
        mini.counter = 0;
        src = readline("mimishell : ");
        if (errno == 13)
            status_exec_g = 126;
        if (src == NULL)
			exit(0);
		ft_mini(&mini, src);
        add_history(src);
        free(src);
    }
    return (0);
}
