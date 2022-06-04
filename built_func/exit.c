/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:37:22 by otmallah          #+#    #+#             */
/*   Updated: 2022/05/31 12:37:39 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_exit(char *str, int fd)
{
	int i;
	int a;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_isdigit(str[i]) == 0)
			{
				write (fd, "exit\n", 6);
				ft_putendl_fd("minishell: exit: numeric argument required", fd);
				status_exec_g = 255;
				exit(255);
			}
			i++;
		}
		a = atoi(str);
		write (fd, "exit\n", 6);
		exit(a);
	}
	printf("exit\n");
	status_exec_g = 0;
	exit(0);
}