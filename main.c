/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:57:56 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/10 21:21:00 by otmallah         ###   ########.fr       */
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

void    ft_mini(t_shell *mini, char *src)
{
    t_list *lst;
    t_list *head;
    int     i;
    lst = ft_parser(src, mini);
    
    // head = lst;
    // while (lst)
    // {
    //     i = 1;
    //     printf("%s -- " , lst->val[0]);
    //     while (lst->val[i])
    //         printf("%s | " , lst->val[i++]);
    //     printf("\n");
    //         lst = lst->next;
    // }
    // lst = head;
    if (!lst)
        return;
    else if (finde_her(lst) == 1)
        pipes(mini, lst);
    else if (finder_red(lst) == 2)
       ft_redirection(mini, lst, 0);
    else if (finder_red(lst) == 4)
        heredoc(mini, lst, 0);
    else if (finder_red(lst) == 3)
        ft_redin(mini, lst);
    else 
       ft_check_built(mini, lst, 1);
}

int main(int ac, char **av, char **env)
{
    char    *src;
    t_shell mini;

   (void)ac;
   (void)av;
    mini.tab_save_env = env;
    mini.tab_save_exp = NULL;
	// signal(SIGINT, checksignal);
    while(1337)
    {
        mini.counter = 0;
        src = readline("mimishell : ");
        ft_mini(&mini, src);
        add_history(src);
        free(src);
    }
    return (0);
}