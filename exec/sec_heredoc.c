/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:34:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/13 15:25:31 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../header/utiles_functions.h"

char **save_cmd(t_list *list)
{
	int i;
	t_list *head;
	char **tab;

	i = 0;
	head = list;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 3)
		{
			if (list->val[2] && i == 0)
				i++;
			else if (list->val[2])
				i++;
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
		if (list->v_type[0] == 3 )
		{
			if (list->val[2] && i == 0)
				tab[i++] = list->val[2];
			else if (list->val[2])
				tab[i++] = list->val[2];
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
	//printf("Tab == %s\n", tab[0]);
	i = 1;
	list = list->next;
	while (list && list->v_type[0] == 3)
	{
		tab = ft_realloc_char(tab);
		tab[i] = list->val[1];
		//printf("Tab == %s\n", tab[i]);
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

void    exec_first_cmd_in_her(t_list *list, t_shell *mini, char *str, int num, int out, int fd)
{
    char **sec_tab;
	int fd_in;

	fd_in = fd_i(list);
	if (num == 1 && out == 1)
	{
		close(mini->all_fd[mini->counter]);
		mini->all_fd[mini->counter] = open(str,  O_RDWR , 0644);
	}
	else
	{
		close(fd);
		fd = open("/tmp/test",  O_RDWR, 0644);
	}
	sec_tab = save_cmd(list);
	int io = 0;
	int lp = 1;
	while (sec_tab[io])
	{
		list->val[lp] = sec_tab[io];
		io++;
		lp++;
	}
	list->val[lp]  = NULL;
	list->v_type[0] = 1;
	list->v_type[1] = 2;
	if (fork() == 0)
	{
		if (out == 1 &&  num == 1)
		{
			int hu;
			hu = dup(mini->all_fd[mini->counter]);
			dup2(hu, 0);
			mini->all_fd[mini->counter] = open(str, O_RDWR, 0644);
			dup2(mini->all_fd[mini->counter], 1);
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
	//else
	//close(fd);
	wait(NULL);
	puts("hani hnaya");
}

void    exec_her(t_list *list, t_shell *mini, int out, int num, char *str, int fd)
{
    char **sec_tab;
	int fd_in;

	fd_in = fd_i(list);
	printf("num %d\n", fd_in);
	if (num == 1 && out == 1)
	{
		close(mini->all_fd[mini->counter]);
		mini->all_fd[mini->counter] = open(str,  O_RDWR, 0644);
	}
	else
	{
		close(fd);
		fd = open("/tmp/test", O_RDWR, 0644);
	}
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
	if (fork() == 0)
	{
		if (out == 1 &&  num == 1)
			dup2(mini->all_fd[mini->counter], 1);
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
	if (out == 1 &&  num == 1)
		close(mini->all_fd[mini->counter]);
	close(fd);
	wait(NULL);  
}

void    heredoc(t_shell *mini, t_list *list, int num)
{
    int out;
    char **tab;
    char *str;
    int fd;
    int i = 0;
    char *find;

    out = open_all_files(list, 1);
    if (list->v_type[0] != 1 && list->v_type[0] == 3)
		tab = save_dele(list);
	else
		tab = save_dele(list->next);
    int size = size_tab(tab);
    if (num == 1 && out == 1)
	{
		mini->save_all_namefiles[mini->counter] = ft_strjoin("/tmp/test", ft_itoa(mini->counter));
		mini->all_fd[mini->counter] = open(mini->save_all_namefiles[mini->counter], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
		fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
    while (1)
	{
		find = readline(">");
		if (find == NULL)
			break ;
		if (strcmp(find, tab[i]) == 0 && tab[i])
		{
			size--;
			i++;
			if (size == 0)
				break;
			if (num == 1 && out == 1)
				mini->all_fd[mini->counter] = open(mini->save_all_namefiles[mini->counter] , O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
		}
		if (num == 1 && out == 1)
			ft_putendl_fd(find, mini->all_fd[mini->counter]);
		else
			ft_putendl_fd(find, fd);
	}
    if (list->v_type[0] == 1 && out != -1)
        exec_first_cmd_in_her(list, mini, mini->save_all_namefiles[mini->counter], num , out, fd);
    else if (out != -1)
        exec_her(list, mini, out,  num, mini->save_all_namefiles[mini->counter], fd);
	puts("***********-----******");
	if (out == -1)
		printf("No such file or directory\n");
	if (num != 1 || out != 1)
		unlink("/tmp/test");
	if (num == 1 && out == 1)
		mini->counter++;
}