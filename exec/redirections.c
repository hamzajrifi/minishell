/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:24:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/05 22:18:42 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int     open_all_files(t_list *list)
{
    int fd;

    while (list)
    {
        if (list->v_type[0] == 6)
            fd = open(list->val[1], O_CREAT | O_RDWR | O_TRUNC , 0644);
        if (list->v_type[0] == 4)
            fd = open(list->val[1], O_CREAT | O_RDWR | O_APPEND , 0644);
        list = list->next;
    }
    return fd;
}

void    ft_redirection(t_shell *mini, t_list *lst, int a)
{
    int fd;
    int id;

    fd = open_all_files(lst);
    id = fork();
    if (id == 0)
    {
        dup2(fd, STDOUT_FILENO);
        ft_check_built(mini, lst, fd);
        //if (a != 1)
        exit(1);
    }
    close(fd);
    wait(NULL);
}

void    ft_redin(t_shell *mini, t_list *lst)
{
    int fd_in;
    int fd_out;

    fd_in = 0;
    fd_out = 1;
    if (lst->v_type[0] == 1)
    {
        fd_in = open(lst->next->next->val[0], O_RDONLY);
        if (fd_in < 0)
            perror(NULL);
        else
        {
            if (lst->next->next->next && lst->next->next->next->v_type[0] == 6)
                fd_out = open_all_files(lst->next);
            if (fork() == 0)
            {
                dup2(fd_in, 0);
                dup2(fd_out, 1);
                exec_cmd(mini, lst);
                exit(1);
            }
            close(fd_in);
            if (fd_out != 1)
                close(fd_out);
            wait(NULL);
        }
    }
    else
    {
        fd_in = open(lst->val[1], O_RDONLY);
        if (fd_in < 0)
            perror(NULL);
    } 
}