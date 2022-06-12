/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:24:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/10 12:04:10 by otmallah         ###   ########.fr       */
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
                //fd = open("/tmp/test", O_CREAT, O_WRONLY, 0444);
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

	i = 0;
	head = list;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4)
		{
			if ((list->val[3] || list->val[2]) && i == 0)
            {
                i++;
                if (list->val[3])
                    i++;
            }
            else if ((list->val[3] || list->val[2]))
            {
                i++;
                if (list->val[3])
                    i++;
            }
		}
		else if (list->v_type[0] == 11)
			break;
		list = list->next;
	}
	tab = (char **)malloc(sizeof(char *) * (i));
	i = 0;
	list = head;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4 )
		{
			if ((list->val[3] || list->val[2]) && i == 0)
            {
				tab[i++] = list->val[2];
                if (list->val[3])
				    tab[i++] = list->val[3];
            }
            else if (list->val[2])
            {
				tab[i++] = list->val[2];
                if (list->val[3])
				    tab[i++] = list->val[3];
            }
		}
		list = list->next;
	}
	tab[i] = NULL;
	return tab;
}

void    ft_redirection(t_shell *mini, t_list *lst, int a)
{
    int fd;
    int id;
    char **tab;
    int io = 0;
    int ij = 0;

    fd = open_all_files(lst, 0);
    if (a != 1 && fd != -1)
    {
        if (lst->v_type[0] != 1 || lst->next->val[2] || lst->next->val[3])
        {
            tab = cmd(lst);
            printf("tab %s\n", tab[0]);
            printf("tab %s\n", tab[1]);
            printf("tab %s\n", tab[2]);
            if (lst->v_type[0] == 1)
                ij = 1;
            while (tab[io])
            {
                lst->val[ij] = strdup(tab[io]);
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
            dup2(fd, STDOUT_FILENO);
            ft_check_built(mini, lst, fd);
            exit(1);
        }
        close(fd);
        wait(NULL);
    }
    else if (fd != -1)
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
    //fd_in = 0;
    fd_out = 1;
    if (lst->v_type[0] == 1)
    {
       lst = lst->next;
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
        if (fd_in != 0)
        {
            if (lst->v_type[0] == 6)
                fd_out =  open_all_files(lst, 0);
            if (fd_out != -1)
            {
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
                break;
            }
            if (lst->next)
                lst = lst->next;
            else
                break;
        }
        if (fd_in != 0)
        {
            if (lst->v_type[0] == 6)
                open_all_files(lst, 0);
        }
    } 
}