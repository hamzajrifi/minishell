/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:07:57 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/11 22:32:29 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

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

// exec_first_cmd

void    exec_first_cmd(t_list *list, t_shell *mini, int *fd)
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
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(fd[1], 1);
		ft_check_built(mini, list, 1);
	}
}

// exec_last_cmd

void    exec_last_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd)
{
    close(fd[0]);
    close(fd[1]);
	if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6)
	{
		dup2(temp_fd, 0);
		ft_redirection(mini, list, 1);
	}
	else if (list->v_type[0] == 8)
	{
        close(temp_fd);
		ft_redin(mini, list);
    }
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(temp_fd, 0);
		ft_check_built(mini, list, 1);
	}
}

// exec_sec_cmd

void    exec_sec_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd)
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
    
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(temp_fd, 0);
		dup2(fd[1], 1);
		ft_check_built(mini, list, 1);
	}
}

int    *exec_first(t_shell *mini, t_list *list , int a)
{
	int *save;
	int count = 0;
	int i = 0;

	save = malloc(sizeof(int) * 10);
	mini->all_fd = (int *)malloc(sizeof(int) * 5);
    while (list && list->next)
    {
        if (list && (list->v_type[0] == 3 || list->next->v_type[0] == 3))
		{
			if (list->v_type[0] == 3)
				save[i] = check_her(list);
			else
				save[i] = check_her(list->next);
			printf("k = %d\n", save[i]);
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
    int id;
    int num_cmd;
    int i;
    int save[100];
    int temp_fd;
    int *k;
    int fs = 0;;

    num_cmd = num_of_cmd(list);
    k = exec_first(mini, list, 1);
    i = 0;
    while (i < mini->counter)
    {
        printf("%d\n", mini->all_fd[i]);
        i++;
    }
    exit(0);
    while (i < num_cmd && list)
    {
        if (pipe(fd) < 0)
            perror("pipe");
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
        save[i] = id;
        i++;
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
			list = list->next->next;
            temp_fd = dup(fd[0]);
        }
        if (list->prev && list->prev->prev && list->prev->prev->v_type[0] == 3)
        {
            if (k[fs] == 0)
            {
                close(mini->all_fd[fs]);
                mini->all_fd[fs] = open("/test/test0", O_RDWR, 0644);
                temp_fd = dup(mini->all_fd[fs]);
                if (fs < mini->counter)
                    fs++;
            }
            else
                temp_fd = dup(fd[0]);
        }
        else
            temp_fd = dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
    }
    while (--i >= 0)
		waitpid(save[i], 0, 0);
}