/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:13:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/04 21:27:55 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void    heredoc(t_shell *mini, t_list *list)
{
	char *find;
	int fd;
	int out;

	out = 1;
	fd = 0;
	while (list)
	{
		puts("hana");
		if (fd == 0)
			fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
		if (list && list->next->next && list->next->next->v_type[0] == 6)
			out = open_all_files(list->next->next); 
		while (1)
		{
			find = readline(">2");
			if (find == NULL)
				break ;
			if (strcmp(find, list->next->val[1]) == 0)
				break;
			ft_putendl_fd(find, fd);
		}
		if (list && list->next->v_type[0] == 3)
		{
			list = list->next;
			puts("heeee");
		}
		else
			break;
	}
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
	unlink("/tmp/test");
}
