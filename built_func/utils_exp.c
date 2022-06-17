/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:04 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 13:22:14 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_realloc(t_shell *index, char *str, int save)
{
	char	**temp;
	int		a;

	a = 0;
	temp = (char **)malloc(sizeof(char *) * (save + 1));
	a = 0;
	while (index->tab_save_exp[a])
	{
		temp[a] = index->tab_save_exp[a];
		a++;
	}
	temp[a] = NULL;
	free(index->tab_save_exp);
	index->tab_save_exp = (char **)malloc(sizeof(char *) * (save + 2));
	a = 0;
	while (temp[a])
	{
		index->tab_save_exp[a] = temp[a];
		a++;
	}
	index->tab_save_exp[a] = str;
	index->tab_save_exp[a + 1] = NULL;
	free(temp);
}

void	ft_print(t_shell *index, int fd)
{
	int	i;

	i = 0;
	while (index->tab_save_env[i])
	{
		ft_putstr_fd("decalre -x ", fd);
		ft_putendl_fd(index->tab_save_env[i], fd);
		i++;
	}
	if (index->tab_save_exp)
	{
		i = 0;
		while (index->tab_save_exp[i])
		{
			ft_putstr_fd("decalre -x ", fd);
			ft_putendl_fd(index->tab_save_exp[i], fd);
			i++;
		}
	}
	status_exec_g = 0;
}

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	duplicate_exp(t_shell *index, char *string, char *add_str, int i)
{
	int		a;
	int		checker;
	char	**temp;
	char	**sec_temp;

	a = len(string);
	checker = len(add_str);
	if (a != 0 && checker != 0)
	{
		temp = ft_split(string, '=');
		sec_temp = ft_split(add_str, '=');
		if (strcmp(temp[0], sec_temp[0]) == 0)
		{
			index->tab_save_exp[i] = add_str;
			return (3);
		}
	}
	else if (a != 0 && checker == 0)
	{
		temp = ft_split(string, '=');
		if (strcmp(temp[0], add_str) == 0)
			return (4);
	}
	else if (a == 0 && checker != 0)
	{
		sec_temp = ft_split(add_str, '=');
		if (strcmp(sec_temp[0], string) == 0)
		{
			index->tab_save_exp[i] = add_str;
			return (5);
		}
	}
	else
	{
		if (strcmp(add_str, string) == 0)
			return (6);
	}
	return (0);
}

int	find_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
