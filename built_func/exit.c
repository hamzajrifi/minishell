/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:37:22 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 12:01:30 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	utils_exit(char *str, int fd, int num, int k)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			write (fd, "exit\n", 6);
			ft_putendl_fd("minishell: exit: numeric argument required", fd);
			status_exec_g = 255;
			if (num != 1)
				exit(255);
			k = 1;
			break ;
		}
		i++;
	}
}

int	print_err(int fd)
{
	ft_putendl_fd("exit", fd);
	ft_putendl_fd("minishell: exit: too many arguments", fd);
	status_exec_g = 1;
	return (-1);
}

void	err(char *str, int num, int fd)
{
	int	a;

	a = atoi(str);
	status_exec_g = a;
	if (num != 1)
	{
		write (fd, "exit\n", 6);
		exit(a);
	}	
}

void	ft_exit(char **str, int fd, int num)
{
	int	i;
	int	a;
	int	k;

	i = 0;
	k = 0;
	if (str)
	{
		if (str[1])
			utils_exit(str[1], fd, num, k);
		if (str[2] && k == 0)
			i = print_err(fd);
		if (i != -1 && k == 0)
			err(str[1], num, fd);
	}
	if (i != -1 && num != 1)
	{
		printf("exit\n");
		status_exec_g = 0;
		if (num != 1)
			exit(0);
	}
}
