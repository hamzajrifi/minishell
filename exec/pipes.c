/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/11 15:40:08 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int		check_her(t_list *list);

int     num_of_cmd(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		if (list->v_type[0] == 1 || list->v_type[0] == 6 || list->v_type[0] == 8 || list->v_type[0] == 3)
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

int    *exec_first(t_shell *mini, t_list *list , int a)
{
	int *save;
	int count = 0;
	int i = 0;

	save = calloc(sizeof(int), 10);
	mini->all_fd = (int *)malloc(sizeof(int) * 5);
    while (list && list->next)
    {
        if (list && (list->v_type[0] == 3 || list->next->v_type[0] == 3))
		{
			if (list->v_type[0] == 3)
				save[i] = check_her(list);
			else
				save[i] = check_her(list->next);
			//printf("k = %d\n", save[i]);
			heredoc(mini, list, a);
			i++;
		}
		if (list->v_type[0] == 3 || list->next->v_type[0] == 3)
		{
			while (list->next && list->next->v_type[0] == 3)
			{
				list = list->next;
			}
		}
		if (list->next)
			list = list->next;
		else
			break;
		count++;
	}
	return save;
}

void    pipes(t_shell *mini, t_list *list)
{
	int fd[2];
	int temp_fd;
	int num_cmd;
	int saver[100];
	int i = 0;
	int id;
	int ffd;
	int *k;

	num_cmd = num_of_cmd(list);
	//printf("%d\n" , num_cmd);
	k = exec_first(mini, list, 1);
	printf("k == %d\n", k[0]);
	// exit(0);
	// exit(0);
	int fs = 0;
	//exit(0);
	i = 0;
	temp_fd = 0;
	int l;
	while (i < num_cmd && list)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		id = fork();
		//puts("hana");
		if (id == 0)
		{
			if (i == 0)
			{
				//puts("11111222233333");
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
				else if (list->v_type[0] == 3 || list->next->v_type[0] == 3)
				{
					puts("hana00000000000000000");
				}
				else if (ft_strcmp(list->val[0], "exit") != 0)
				{
					printf("val == %s\n", list->val[0]);
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
				{
					close(temp_fd);
					ft_redin(mini, list);
				}
				else if (ft_strcmp(list->val[0], "exit") != 0)	
				{
					printf("val  == %s\n", list->val[0]);
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
					printf("ll = %s\n", list->val[0]);
					dup2(temp_fd, 0);
					dup2(fd[1], 1);
					ft_check_built(mini, list, 1);
				}
			}
			exit(0);
		}
		saver[i] = id;
		temp_fd = fd[0];
		if (list && list->next && (list->next->v_type[0] == 6 || list->next->v_type[0] == 8 || list->next->v_type[0] == 3 || list->v_type[0] == 3) && list->next->next)
		{
			while (list && list->next && list->v_type[0] != 11)
			{
				list = list->next;
			}
			list = list->next;
		}
		else if (list->next)
		{
			puts("ya latife");
			list = list->next->next;
			temp_fd = dup(fd[0]);
		}
		close(fd[0]);
		close(fd[1]);
		//printf("i = %d\n", i);
		i++;
	}
	unlink("/tmp/test");
	while (--i >= 0)
		waitpid(saver[i], 0, 0);
}


int		check_her(t_list *list)
{
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4)
			return 1;
		list = list->next;
	}
	return 0;
}