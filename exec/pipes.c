/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/10 20:53:47 by otmallah         ###   ########.fr       */
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
	int save[100];
	int count = 0;
	int i = 0;

    while (list && list->next)
    {
        if (list && (list->v_type[0] == 3 || list->next->v_type[0] == 3))
		{
			if (list->v_type[0] == 3)
				save[i] = check_her(list);
			else
				save[i] = check_her(list->next);
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
	int i;
	int id;
	int ffd;
	int *k;

	num_cmd = num_of_cmd(list);
	//printf("%d\n" , num_cmd);
	k = exec_first(mini, list, 1);
	// exit(0);
	// exit(0);
	//printf("k = %d\n", k[0]);
	// printf("k = %d\n", k[1]);
	i = 0;
	int fs = 0;
	temp_fd = 0;
	int l;
	while (i < num_cmd && list)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		// if (list->v_type[0] == 3 || list->next->v_type[0] == 3)
		// 	l = 1;
		// else
		// 	l = 0;
		id = fork();
		//puts("hana");
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
				else if (list->v_type[0] == 3 || list->next->v_type[0] == 3)
				{}
				else if (ft_strcmp(list->val[0], "exit") != 0)
				{
					printf("%s\n", list->val[0]);
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
				else if (list->v_type[0] == 3)
				{
					close(temp_fd);
				}
				else if (ft_strcmp(list->val[0], "exit") != 0)	
				{
					// printf("ks = %d\n", k[fs]);
					// if (k[fs] == 0)
						// dup2(mini->all_fd[fs], 0);
					// else
					printf("%s\n", list->val[0]);
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
					//printf("ll = %s\n", list->val[0]);
					// if (k[fs] == 0)
					// {
						// close(temp_fd);
						//close(fd[1]);
						// dup2(mini->all_fd[fs], 0);
					// }
					// else
					// {
					dup2(temp_fd, 0);
					dup2(fd[1], 1);
					ft_check_built(mini, list, 1);
				}
			}
			exit(0);
		}
		saver[i] = id;
		if (list && (list->v_type[0] == 3))
		{
			puts("haanaa");
			temp_fd = dup(mini->all_fd[fs]);
			if (mini->counter - 1 > fs)
				fs++;
		}
		else if (i != (num_cmd - 1))
			temp_fd = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		// if (list->v_type[0] == 3 || list->next->v_type[0]  == 3)
		// 	fs++;
		//printf("fs == %d\n", fs);
		if (list && list->next && (list->next->v_type[0] == 6 || list->next->v_type[0] == 8 || list->next->v_type[0] == 3 || list->v_type[0] == 3) && list->next->next)
		{
			while (list && list->next && list->v_type[0] != 11)
			{
				list = list->next;
			}
			list = list->next;
			//printf("val == %s\n", list->val[0]);
		}
		else if (list->next)
			list = list->next->next;
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