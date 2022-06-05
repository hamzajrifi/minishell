/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:13:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/05 19:57:58 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../header/utiles_functions.h"
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

void    heredoc(t_shell *mini, t_list *list)
{
	char *find;
	int fd;
	int out;
	int i;
	char **tab;

	out = 1;
	i = 0;
	fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
	//if (list && list->next && list->next->next && list->next->next->v_type[0] == 6)
	out = open_all_files(list);
	if (list->v_type[0] != 1)
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
		}
		ft_putendl_fd(find, fd);
	}
	if (list->v_type[0] == 1)
	{
		close(fd);
		fd = open("/tmp/test", O_CREAT | O_RDWR, 0644);
		if (fork() == 0)
		{
			dup2(fd, 0);
			dup2(out, 1);
			ft_check_built(mini, list, 1);
			exit(0);
		}
		close(fd);
		wait(NULL);
	}
	unlink("/tmp/test");
}
