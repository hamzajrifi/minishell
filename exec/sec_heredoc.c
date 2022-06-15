/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:34:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/14 15:50:28 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../header/utiles_functions.h"

char **save_cmd(t_list *list)
{
	int i;
	t_list *head;
	char **tab;
	int k = 2;

	i = 0;
	head = list;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 3 || list->v_type[0] == 6)
		{
			while (list->val[k])
			{
				k++;
				i++;
			}
			k = 2;
		}
		list = list->next;
	}
	tab = (char **)malloc(sizeof(char *) * (i));
	i = 0;
	list = head;
	k = 2;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 3 || list->v_type[0] == 6 || list->v_type[0] == 8)
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

char	**save_dele(t_list *list)
{
	int i;
	char **tab;

	tab = malloc(sizeof(char *)* 2);
	tab[1] = 0;
	tab[0] = ft_strdup(list->val[1]);
	i = 1;
	list = list->next;
	while (list && list->v_type[0] == 3)
	{
		tab = ft_realloc_char(tab);
		tab[i] = list->val[1];
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return tab;
}

int size_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return i;
}

int fd_i(t_list *list)
{
	int fd;

	fd = 0;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 8)
			fd = open(list->val[1], O_RDWR, 0644);
		list = list->next;
	}
	return fd;
}

void    exec_first_cmd_in_her(t_list *list, t_shell *mini, int fd_out, int num, int out, int fd)
{
    char **sec_tab;
	int fd_in;

	fd_in = fd_i(list);
	close(fd);
	fd = open("/tmp/test",  O_RDWR, 0644);
	sec_tab = save_cmd(list);
	int io = 0;
	int lp = 1;
	if (sec_tab[0])
	{
		while (sec_tab[io])
		{
			list->val[lp] = sec_tab[io];
			io++;
			lp++;
		}
		list->val[lp]  = NULL;
		list->v_type[0] = 1;
		list->v_type[1] = 2;
	}
	ft_exit_status(mini, list);
	if (fork() == 0)
	{
		if (out == 1 &&  num == 1)
		{
			dup2(fd, 0);
			if (mini->counter == mini->num_ofall_cmd)
				dup2(1, 1);
			else
				dup2(fd_out, 1);
		}
		else
		{
			if (fd_in != 0)
				dup2(fd_in, 0);
			else
				dup2(fd, 0);
			dup2(out, 1);
		}
		ft_check_built(mini, list, 1);
		exit(0);
	}
	wait(NULL);
}

void    exec_her(t_list *list, t_shell *mini, int out, int num, int fd_out, int fd)
{
    char **sec_tab;
	int fd_in;
	

	fd_in = fd_i(list);
	close(fd);
	fd = open("/tmp/test", O_RDWR, 0644);
	sec_tab = save_cmd(list);
	int io = 0;
	if (sec_tab[1])
	{
		while (list->val[io])
		{
			list->val[io] = sec_tab[io];
			io++;
		}
		list->v_type[0] = 1;
		list->v_type[1] = 2;
	}
	else if (sec_tab[0])
	{
		list->val[0] = sec_tab[0];
		list->val[1] = NULL;
		list->v_type[0] = 1;
		list->v_type[1] = 2;
	}
	ft_exit_status(mini, list);
	if (fork() == 0)
	{
		if (out == 1 &&  num == 1)
		{
			dup2(fd, 0);
			if (mini->counter == mini->num_ofall_cmd)
				dup2(1, 1);
			else
				dup2(fd_out, 1);
		}
		else
		{
			if (fd_in != 0)
				dup2(fd_in, 0);
			else
				dup2(fd, 0);
			dup2(out, 1);
		}
		ft_check_built(mini, list, 1);
		exit(0);
	}
	wait(NULL);  
}

void    heredoc(t_shell *mini, t_list *list, int num, int fd_out)
{
    int out;
    char **tab;
    char *str;
    int fd;
    int i = 0;
    char *find;
	
    if (list->v_type[0] != 1 && list->v_type[0] == 3)
		tab = save_dele(list);
	else
		tab = save_dele(list->next);
    int size = size_tab(tab);
	fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
    while (1)
	{
		find = readline("> ");
		if (find == NULL)
			break ;
		if (strcmp(find, tab[i]) == 0 && tab[i])
		{
			size--;
			i++;
			if (size == 0)
				break;
			else
				fd = open("/tmp/test", O_RDWR | O_TRUNC , 0644);
		}
		ft_putendl_fd(find, fd);
	}
    out = open_all_files(list, 1);
    if (list->v_type[0] == 1 && out != -1)
        exec_first_cmd_in_her(list, mini, fd_out, num , out, fd);
    else if (out != -1)
        exec_her(list, mini, out,  num, fd_out, fd);
	if (out == -1)
		printf("No such file or directory\n");
	if (num != 1 || out != 1)
		unlink("/tmp/test");
	if (num == 1 && out == 1)
		mini->counter++;
}