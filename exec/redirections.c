/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:24:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/13 14:40:11 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int     open_all_files(t_list *list, int a)
{
    int fd;
    int fd_in;

    fd = 1;
    while (list && list->v_type[0] != 11)
    {
        if (list->v_type[0] == 6)
            fd = open(list->val[1], O_CREAT | O_RDWR | O_TRUNC , 0644);
        if (list->v_type[0] == 4)
            fd = open(list->val[1], O_CREAT | O_RDWR | O_APPEND , 0644);
        if (list->v_type[0] == 8)
        {
            fd_in = open(list->val[1], O_RDWR, 0666);
            if (fd_in < 0)
            {
                if (a != 1)
                    perror(NULL);
                fd = -1;
                return fd;
            }
        }
        list = list->next;
    }
    return fd;
}

char  **cmd(t_list *list)
{
	int i;
	t_list *head;
	char **tab;
    int k = 2;

	i = 0;
	head = list;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4 || list->v_type[0] == 8)
		{
            while (list->val[k])
            {
                i++;
                k++;
            }
            k = 2;
		}
		else if (list->v_type[0] == 11)
			break;
		list = list->next;
	}
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
    k = 2;
	list = head;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4 || list->v_type[0] == 8)
		{
            while (list->val[k])
            {
                tab[i++] = list->val[k];
                k++;
            }
            k = 2;
		}
		list = list->next;
	}
	tab[i] = NULL;
	return tab;
}

void    ft_redirection(t_shell *mini, t_list *lst, int a, int tem_fd)
{
    int fd;
    int id;
    char **tab;
    int io = 0;
    int ij = 0;

    fd = open_all_files(lst, 0);
    if (fd != -1)
    {
        tab = cmd(lst);
        if (tab)
        {
            if (lst->v_type[0] == 1)
                ij = 1;
            while (tab[io])
            {
                lst->val[ij] = tab[io];
                io++;
                ij++;
            }
            lst->val[ij]  = NULL;
            lst->v_type[0] = 1;
            lst->v_type[1] = 2;
        }
        id = fork();
        if (id == 0)
        {
            if (fd != 1)
                dup2(fd, STDOUT_FILENO);
            else
                dup2(tem_fd, 0);
            ft_check_built(mini, lst, fd);
            exit(0);
        }
        close(fd);
        wait(NULL);
    }
    unlink("/tmp/test");
}

void    ft_redin(t_shell *mini, t_list *lst, int te_fd, int num)
{
    int fd_in;
    int fd_out;
    int i = 0, j = 0;
    t_list *head;
    char **tab;

    head = lst;
    fd_out = 1;
    int k = 2;
    if (lst->v_type[0] == 1)
    {
        lst = lst->next;
        fd_out =  open_all_files(lst, 0);
        while (lst && lst->v_type[0] == 8)
        {
            if (lst->val[k])
            {
                while (lst && lst->val[k])
                {
                    fd_in = open(lst->val[k], O_RDONLY, 0444);
                    if (fd_in < 0)
                    {
                        fd_in = 0;
                        perror(NULL);
                        break;
                    }
                    k++;
                }
            }
            else
                fd_in = open(lst->val[1], O_RDONLY, 0444);
            k = 2;
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
        lst = head;
        tab = cmd(lst);
        if (tab)
        {
            if (lst->v_type[0] == 1)
                i = 1;
            while (tab[i])
            {
                lst->val[i] = tab[j];
                i++;
                j++;
            }
            lst->val[i]  = NULL;
            lst->v_type[0] = 1;
            lst->v_type[1] = 2;
        }
        if (fd_in != 0)
        {
            if (fd_out != -1)
            {
                //lst = head;
                if (fork() == 0)
                {
                    dup2(fd_in, 0);
                    if (num == 1 && fd_out == 1)
                        dup2(te_fd, 1);
                    else
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
    }
    else
    {
        fd_out = open_all_files(lst, 0);
        while (lst && lst->v_type[0] == 8)
        {
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
        lst = head;
        tab = cmd(lst);
        if (tab)
        {
            while (tab[i])
            {
                lst->val[i] = tab[i];
                i++;
            }
            lst->val[i]  = NULL;
            lst->v_type[0] = 1;
            lst->v_type[1] = 2;
        }
        if (fd_in != 0)
        {
            if (fd_out != -1)
            {
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
    } 
}