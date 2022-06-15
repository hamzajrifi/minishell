/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:37:22 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/14 16:47:27 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_exit(char **str, int fd)
{
	int i;
	int a;

	i = 0;
	if (str)
	{
		while (str[1][i])
		{
			if (ft_isdigit(str[1][i]) == 0)
			{
				write (fd, "exit\n", 6);
				ft_putendl_fd("minishell: exit: numeric argument required", fd);
				status_exec_g = 255;
				exit(255);
			}
			i++;
		}
		if (str[2])
		{
			ft_putendl_fd("exit", fd);
			ft_putendl_fd("minishell: exit: too many arguments", fd);
			i = -1;
		}
		if (i != -1)
		{
			a = atoi(str[1]);
			write (fd, "exit\n", 6);
			exit(a);
		}
	}
	if (i != -1)
	{
		printf("exit\n");
		status_exec_g = 0;
		exit(0);
	}
}