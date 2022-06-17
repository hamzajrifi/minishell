/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:55 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 13:17:31 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_pwd(int fd)
{
	char	buff[256];

	ft_putendl_fd(getcwd(buff, sizeof(buff)), fd);
}

int	loop(t_shell *mini)
{
	int		i;
	char	**temp;

	i = 0;
	while (mini->tab_save_exp[i])
	{
		temp = ft_split(mini->tab_save_exp[i], '=');
		if (strcmp(temp[0], "HOME") == 0)
		{
			chdir(temp[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_13(t_shell *index, char *str, char **save, char **temp)
{
	norme4(index, temp, str, save);
	if (index->tab_save_exp)
		unset_exp(index, str);
	status_exec_g = 0;
}
