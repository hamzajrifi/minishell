/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/06 19:01:05 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int     num_of_cmd(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		if (list->v_type[0] == 1 || list->v_type[0] == 6 || list->v_type[0] == 8)
		{
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
    while (list && list->next)
    {
        if (list && (list->v_type[0] == 3 || list->next->v_type[0] == 3))
		{
			heredoc(mini, list);
		}
		if (list->v_type[0] == 3 || list->next->v_type[0] == 3)
		{
			while (list->next && list->next->v_type[0] == 3)
				list = list->next;
		}
		if (list->next)
			list = list->next;
		else
			break;
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
	exec_first(mini, list);
	i = 0;
	temp_fd = 0;
	while (i < num_cmd && list)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		id = fork();
		if (id == 0)
		{
			if (i == 0)
			{
				close(fd[0]);
				if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6)
				{
					close(fd[1]);
					ft_redirection(mini, list, 1);
				}
				else if (list->v_type[0] == 8)
				{
					close(fd[1]);
					ft_redin(mini, list);
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
				if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6)
					ft_redirection(mini, list, 1);
				else if (list->v_type[0] == 8)
					ft_redin(mini, list);
				else if (ft_strcmp(list->val[0], "exit") != 0)	
				{
					dup2(temp_fd, 0);
					ft_check_built(mini, list, 1);
				}
			}
			else
			{
				close(fd[0]);
				if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6)
				{
					close(fd[1]);
					dup2(temp_fd, 0);
					ft_redirection(mini, list, 1);
				}
				else if (list->v_type[0] == 8)
				{
					close(fd[1]);
					ft_redin(mini, list);
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
		temp_fd = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		if (list && list->next && (list->next->v_type[0] == 6 || list->next->v_type[0] == 8 || list->next->v_type[0] == 3) && list->next->next)
		{
			while (list && list->next && list->v_type[0] != 11)
				list = list->next;
			list = list->next;
		}
		else if (list->next)
			list = list->next->next;
		i++;
	}
	while (--i >= 0)
		waitpid(saver[i], 0, 0);
}