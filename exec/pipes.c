/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/04 21:41:28 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int     num_of_cmd(t_list *list)
{
    int count;

    count = 0;
    while (list)
    {
        if (list->val)
            count++;
        if (list->next)
            list = list->next->next;
        else 
            break;
    }
    return count;
}

void    pipes(t_shell *mini, t_list *list)
{
    int fd[2];
    int temp_fd;
    int num_cmd;
    int saver[100];
    int i;
    int id;
    t_list *temp;

    temp = list;
    num_cmd = num_of_cmd(list);
    i = 0;
    temp_fd = 0;
    while (i < num_cmd && list)
    {
        if (pipe(fd) < 0)
            perror("pipe");
        id = fork();
        if (id == 0)
        {
            if (i == 0)
            {
                close(fd[0]);
                dup2(fd[1], 1);
                if (ft_strcmp(list->val[0], "exit") != 0)
                    ft_check_built(mini, list, 1);
            }
            else if (i == (num_cmd - 1))
            {
                close(fd[0]);
                close(fd[1]);
                dup2(temp_fd, 0);
                if (ft_strcmp(list->val[0], "exit") != 0)
                    ft_check_built(mini, list, 1);
            }
            else
            {
                close(fd[0]);
                dup2(temp_fd, 0);
                dup2(fd[1], 1);
                if (ft_strcmp(list->val[0], "exit") != 0)
                    ft_check_built(mini, list, 1);
            }
            exit(0);
        }
        saver[i] = id;
        temp_fd = dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        if (list->next)
            list = list->next->next;
        i++;
    }
    while(--i >= 0)
        waitpid(saver[i], 0, 0);
}