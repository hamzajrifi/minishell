/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:24:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/06 19:52:08 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int     open_all_files(t_list *list)
{
    int fd;
    int fd_in;

    while (list && list->v_type[0] != 11)
    {
        //puts("here");
        if (list->v_type[0] == 6)
            fd = open(list->val[1], O_CREAT | O_RDWR | O_TRUNC , 0644);
        if (list->v_type[0] == 4)
            fd = open(list->val[1], O_CREAT | O_RDWR | O_APPEND , 0644);
        if (list->v_type[0] == 8)
        {
            fd_in = open(list->val[1], O_RDWR, 0666);
            if (fd_in < 0)
            {
                perror(NULL);
                fd = open("/tmp/test", O_CREAT, O_WRONLY, 0444);
                return fd;
            }
        }
        list = list->next;
    }
    return fd;
}

void    ft_redirection(t_shell *mini, t_list *lst, int a)
{
    int fd;
    int id;

    fd = open_all_files(lst);
    if (a != 1)
    {
        id = fork();
        if (id == 0)
        {
            dup2(fd, STDOUT_FILENO);
            ft_check_built(mini, lst, fd);
            exit(1);
        }
        close(fd);
        wait(NULL);
    }
    else
    {
        dup2(fd, 1);
        ft_check_built(mini, lst, fd);
        close(fd);
    }
    unlink("/tmp/test");
}

void    ft_redin(t_shell *mini, t_list *lst)
{
    int fd_in;
    int fd_out;
    t_list *head;

    head = lst;
    fd_in = 0;
    fd_out = 1;
    if (lst->v_type[0] == 1)
    {
       lst = lst->next;
       printf("%s\n", lst->val[1]);
        while (lst && lst->v_type[0] == 8)
        {
            puts("hana");
            fd_in = open(lst->val[1], O_RDONLY, 0444);
            if (fd_in < 0)
            {
                fd_in = 0;
                perror(NULL);
                break;
            }
            if (lst->next)
                lst = lst->next;
            else
                break;
        }
        puts("hana");
        if (fd_in != 0)
        {
            if (lst->v_type[0] == 6)
                fd_out =  open_all_files(lst);
            lst = head;
            if (fork() == 0)
            {
                dup2(fd_in, 0);
                dup2(fd_out, 1);
                exec_cmd(mini, lst);
                exit(0);
            }
            close(fd_in);
            if (fd_out != 1)
                close(fd_out);
            wait(NULL);
        }
    }
    else
    {
        while (lst && lst->v_type[0] == 8)
        {
            fd_in = open(lst->val[1], O_RDONLY);
            if (fd_in < 0)
            {
                fd_in = 0;
                perror(NULL);
            }
            if (lst->next)
                lst = lst->next;
            else
                break;
        }
        if (fd_in != 0)
        {
            if (lst->v_type[0] == 6)
                open_all_files(lst);
        }
    } 
}