/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 19:46:38 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int		check_her(t_list *list)
{
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4)
			return (1);
		list = list->next;
	}
	return (0);
}

int     num_of_cmd(t_list *list)
{
	int	count;
	int	is_her;

	count = 0;
	while (list)
	{
		is_her = 0;
		while (list && list->v_type[0] != 11)
			list = list->next;
		if (is_her == 0)
			count++;
		if (list)
			list = list->next;
	}
	return (count);
}

void	exec_first_cmd(t_list *list, t_shell *mini, int *fd)
{
	close(fd[0]);
	if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6 ||
		 list->v_type[0] == 4 || (list->next && list->next->v_type[0] == 4) )
		ft_redirection(mini, list, 1, fd[1]);
	else if ((list->next && list->next->v_type[0] == 8) || list->v_type[0] == 8)
		ft_redin(mini, list, fd[1], 1);
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(fd[1], 1);
		ft_check_built(mini, list, 1);
	}
}

void	exec_last_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd)
{
	if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6 ||
		list->v_type[0] == 4 || (list->next && list->next->v_type[0] == 4) )
	{
		dup2(temp_fd, 0);
		ft_redirection(mini, list, 1, fd[1]);
	}
	else if ((list->next && list->next->v_type[0] == 8) || list->v_type[0] == 8)
	{
		close(temp_fd);
		ft_redin(mini, list, fd[1], 1);
	}
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(temp_fd, 0);
		ft_check_built(mini, list, 1);
	}
}

void	exec_sec_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd)
{
	close(fd[0]);
	if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6 ||
		list->v_type[0] == 4 || (list->next && list->next->v_type[0] == 4) )
	{
		dup2(temp_fd, 0);
		ft_redirection(mini, list, 1, fd[1]);
	}
	else if ((list->next && list->next->v_type[0] == 8) || list->v_type[0] == 8)
		ft_redin(mini, list, fd[1], 1);
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(fd[1], 1);
		dup2(temp_fd, 0);
		ft_check_built(mini, list, 1);
	}
}


void    pipes(t_shell *mini, t_list *list)
{
	int fd[2];
	int id;
	int num_cmd;
	t_list *head = list;
	int i;
	int *save;
	int temp_fd;
	int fs = 0;;
	num_cmd = num_of_cmd(list);
	mini->num_ofall_cmd = num_cmd;
	save =  malloc(sizeof(int) * num_cmd);
	int cnt = 0;
	i = 0;
	while (i < num_cmd && list)
	{
		ft_exit_status(mini, list);
		if (pipe(fd) < 0)
			perror("pipe");
		if (list && ft_strcmp(list->val[0], "exit") == 0 && list->val[1])
			ft_exit(list->val, 1, 1);
		else if (i == 0 && (TEST_HACK1 || TEST_HACK2 || TEST_HACK3 || TEST_HACK4))
			cnt = 2;
		else if ((list->next && list->next->v_type[0] == 3) || list->v_type[0] == 3)
		{
			mini->counter = i + 1;
			heredoc(mini, list, 1, fd[1]);
			wait(NULL);
		}
		else
		{
			puts("tayaaaaa7");
			mini->counter = i + 1;
			id = fork();
			if (id == 0)
			{
				if (i == 0)
					exec_first_cmd(list, mini, fd);
				else if (i == (num_cmd - 1))
					exec_last_cmd(list, mini, temp_fd, fd);
				else
					exec_sec_cmd(list, mini, temp_fd, fd);
				exit(0);
			}
			save[fs] = id;
			fs++;
		}
		temp_fd = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		i++;
 		if (list && list->next && (list->next->v_type[0] == 6 || list->next->v_type[0] == 8 || list->next->v_type[0] == 3 || list->next->v_type[0] == 4  || list->v_type[0] == 3) && list->next->next)
		{
			while (list && list->next && list->v_type[0] != 11)
			{
				list = list->next;
			}
			list = list->next;
		}
		else if (list->next)
		{
			mini->counter++;
			list = list->next->next;
		}
	}
	if (cnt == 2)
	{
		list = head;
		int fd = open("/tmp/test", O_CREAT | O_RDWR);
		id = fork();
		if (id == 0)
		{
			if (list->next && (list->next->v_type[0] == 6 || list->next->v_type[0] == 4))
			{
				ft_redirection(mini, list, 1, 1);
			}
			else if ((list->next && list->next->v_type[0] == 8) || list->v_type[0] == 8)
			{
				ft_redin(mini, list, fd, 1);
			}
			else
			{
				dup2(fd, 1);
				exec_cmd(mini, list);
			}
			exit(0);
		}
		save[fs] = id;
	}
	while (fs >= 0)
	{
		waitpid(save[fs], 0, 0);
		fs--;
	}
	unlink("/tmp/test");
}
