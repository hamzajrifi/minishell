/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:37:22 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/16 12:01:26 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_exit(char **str, int fd, int num)
{
	int i;
	int a;
	int k = 0;

	i = 0;
	if (str)
	{
		if (str[1])
		{
			while (str[1][i])
			{
				if (ft_isdigit(str[1][i]) == 0)
				{
					write (fd, "exit\n", 6);
					ft_putendl_fd("minishell: exit: numeric argument required", fd);
					status_exec_g = 255;
					if (num != 1)
						exit(255);
					k = 1;
					break;
				}
				i++;
			}
		}
		if (str[2] && k == 0)
		{
			ft_putendl_fd("exit", fd);
			ft_putendl_fd("minishell: exit: too many arguments", fd);
			status_exec_g = 1;
			i = -1;
		}
		if (i != -1 && k == 0)
		{
			a = atoi(str[1]);
			status_exec_g = a;
			if (num != 1)
			{
				write (fd, "exit\n", 6);
				exit(a);
			}
		}
	}
	if (i != -1 && num != 1)
	{
		printf("exit\n");
		status_exec_g = 0;
		if (num != 1)
			exit(0);
	}
}