/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:33:09 by otmallah          #+#    #+#             */
/*   Updated: 2022/05/26 19:29:05 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    ft_or_bonus(t_shell *mini, char *str)
{
    int id;
    char **tab;
    int i;
    int wstatus;
    int status_ex;

    i = 0;
    tab = ft_split(str, '|');
    while (tab[i])
    {
        if (find_pipe(tab[i]) == 1)
        {
            ft_pipe(mini, tab[i]);
        }
        else
        {
            id = fork();
            if (id == 0)
            {
                check_built(mini, tab[i], 1, 1);
                exit(0);
            }
            else
            {
                wait(&wstatus);
                if (WIFEXITED(wstatus))
                    status_ex = WEXITSTATUS(wstatus);
            }
            if (status_ex == 1)
            {
                
            }
            if (exec_pipe(mini, tab[i]) == 1)
                break;
        }
        i++;
    }
    
}