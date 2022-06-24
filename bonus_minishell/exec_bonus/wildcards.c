/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:09:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 23:40:20 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	one_wild(t_list **list, t_wild *wild, int fd)
{
	wild->get_next = get_next_line(fd);
	while (wild->get_next)
	{
		wild->tab_wild[wild->size_j] = wild->get_next;
		wild->size_j++;
		wild->get_next = get_next_line(fd);
	}
}

void	err_wild(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": minishell : no such file or directory\n", 41);
}

void	import_all_arg(t_shell *mini, t_list **list, t_wild *wild, int fd)
{
	char	**tab;
	int		k;
	int		j;
	int		size;

	k = 1;
	close(fd);
	fd = open("/tmp/test1", O_RDWR, 0644);
	while (*list && (*list)->val[k])
	{
		size = wild->size_j;
		tab = ft_split((*list)->val[k], '*');
		if (!tab[0])
			one_wild(list, wild, fd);
		else
			mult_wild(list, wild, tab, fd);
		close(fd);
		fd = open("/tmp/test1", O_RDWR, 0644);
		k++;
		if (size == wild->size_j)
			err_wild((*list)->val[k - 1]);
		size = wild->size_j;
	}
	wild->tab_wild[wild->size_j] = NULL;
	if (wild->size_j != 0)
		change(list, wild);
}

void	exec_wild(t_shell *mini, t_list **list)
{
	char	**temp;
	char	*str;

	str = check_path_if_exi(mini);
	if (str)
	{
		temp = ft_split(str, ':');
		if (temp[0])
			ft_execve(temp, mini, *list);
		ft_err((*list)->val[0]);
	}
	ft_err((*list)->val[0]);
}

void	utils_exec_wild(t_wild *wild, t_shell *mini, t_list **list)
{
	if (fork() == 0)
	{
		if (wild->out_file != 1)
			dup2(wild->out_file, 1);
		if (wild->in_file != 0)
			dup2(wild->in_file, 0);
		exec_wild(mini, list);
	}
	wait(NULL);
}

void	ft_wildcards(t_list **list, t_shell *mini)
{
	char	**tab;
	char	**exec;
	int		fd;
	t_wild	wild;

	wild.size = 0;
	wild.size_j = 0;
	wild.tab_wild = (char **)malloc(sizeof(char *) * 50);
	exec = (char **)malloc(sizeof(char *) * 2);
	exec[0] = "ls";
	exec[1] = NULL;
	wild.out_file = open_all_files(*list, 2);
	wild.in_file = utils_redin(*list);
	unlink("/tmp/test1");
	fd = open("/tmp/test1", O_CREAT | O_RDWR, 0644);
	if (fork() == 0)
	{
		dup2(fd, 1);
		execve("/bin/ls", exec, mini->tab_save_env);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
	import_all_arg(mini, list, &wild, fd);
	utils_exec_wild(&wild, mini, list);
}
