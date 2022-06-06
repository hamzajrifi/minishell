/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/06 16:50:11 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int     num_of_cmd(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		if (list->v_type[0] == 1)
		{
			//printf("%s\n", list->val[0]);
			count++;
		}
		if (list->next)
			list = list->next;
		else 
			break;
	}
	return count;
}

void    exec_first(t_shell *mini, t_list *list)
{
    while (list)
    {
        if (list->next && list->next->v_type[0] == 6)
			ft_redirection(mini, list, 1);
		list = list->next->next;
    }
}

void    pipes(t_shell *mini, t_list *list)
{
	int fd[2];
	int temp_fd;
	int num_cmd;
	int saver[100];
	int i;
	int id;

	num_cmd = num_of_cmd(list);
	//printf("num = %d\n", num_cmd);
	//exec_first(mini, list);
	//exit(0);
	i = 0;
	temp_fd = 0;
	while (i < num_cmd && list)
	{
		puts("hhahahahahahahahahaha");

		if (pipe(fd) < 0)
			perror("pipe");
		id = fork();
		if (id == 0)
		{
			if (i == 0)
			{
				close(fd[0]);
				if (list->next && list->next->v_type[0] == 6)
				{
					close(fd[1]);
					ft_redirection(mini, list, 1);
				}
				else if (ft_strcmp(list->val[0], "exit") != 0)
				{
					dup2(fd[1], 1);
					ft_check_built(mini, list, 1);
				}
			}
			else if (i == (num_cmd - 1))
			{
				close(fd[0]);
				close(fd[1]);
				dup2(temp_fd, 0);
				if (list->next && list->next->v_type[0] == 6)
				{
					ft_redirection(mini, list, 1);
				}
				else if (ft_strcmp(list->val[0], "exit") != 0)	
				{
					dup2(temp_fd, 0);
					ft_check_built(mini, list, 1);
				}
			}
			else
			{
				close(fd[0]);
				if (list->next && list->next->v_type[0] == 6)
				{
					close(fd[1]);
					dup2(temp_fd, 0);
					ft_redirection(mini, list, 1);
				}
				else if (ft_strcmp(list->val[0], "exit") != 0)
				{
					dup2(temp_fd, 0);
					dup2(fd[1], 1);
					ft_check_built(mini, list, 1);
				}
			}
			exit(0);
		}
		saver[i] = id;
		//if (list->next && list->next->v_type[0] != 6)
		temp_fd = dup(fd[0]);
		//printf("%d\n", temp_fd);
		close(fd[0]);
		close(fd[1]);
		if (list && list->next && list->next->v_type[0] == 6 && list->next->next)
		{
			while (list && list->next && list->v_type[0] != 11 )
			{
				puts("hana");
				list = list->next;
			}
			list = list->next;
		}
		else if (list->next)
		{
			//puts("hana");
			list = list->next->next;
		}
		i++;
	}
	while (--i >= 0)
		waitpid(saver[i], 0, 0);
}