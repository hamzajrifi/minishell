/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:13:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/09 18:30:00 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../header/utiles_functions.h"

char **save_cmd(t_list *list);

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

void    heredoc(t_shell *mini, t_list *list, int num, int pipe_fd)
{
	char *find;
	int fd;
	int out;
	int i;
	char **tab;
	char **sec_tab;

	out = 1;
	i = 0;
	fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
	out = open_all_files(list);
	if (list->v_type[0] != 1 && list->v_type[0] == 3)
		tab = save_dele(list);
	else
		tab = save_dele(list->next);
	int size = size_tab(tab);
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
			else
				fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
		}
		else
			ft_putendl_fd(find, fd);
	}
	if (list->v_type[0] == 1)
	{
		close(fd);
		fd = open("/tmp/test", O_CREAT | O_RDWR, 0644);
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
			dup2(fd, 0);
			if (out == 1 &&  num == 1)
				dup2(pipe_fd, 1);
			else
				dup2(out, 1);
			ft_check_built(mini, list, 1);
			exit(0);
		}
		close(fd);
		wait(NULL);
	}
	else
	{
		close(fd);
		fd = open("/tmp/test", O_CREAT | O_RDWR, 0644);
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
			dup2(fd, 0);
			if (out == 1 &&  num == 1)
				dup2(pipe_fd, 1);
			else
				dup2(out, 1);
			ft_check_built(mini, list, 1);
			exit(0);
		}
		close(fd);
		wait(NULL);
	}
	if (num != 1 && out != 1)
		unlink("/tmp/test");
}


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