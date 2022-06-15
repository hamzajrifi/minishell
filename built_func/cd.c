/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:15:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/14 19:05:57 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	go_home(t_shell *mini)
{
	int i;
	char **temp;

	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(temp[0], "HOME") == 0)
		{
			chdir(temp[1]);
			return 1;
		}
		i++;
	}
	if (mini->tab_save_exp)
	{
		i = 0;
		while (mini->tab_save_exp[i])
		{
			temp = ft_split(mini->tab_save_exp[i], '=');
			if (strcmp(temp[0], "HOME") == 0)
			{
				chdir(temp[1]);
				return 1;
			}
			i++;
		}
	}
	return 0;
}

int		find_slash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return 1;
		i++;
	}
	return 0;
}

void	change_pwd(t_shell *mini)
{
	int i;
	char **str;
	char buff[256];

	i = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(str[0], "PWD") == 0)
		{
			str[0] = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
			mini->tab_save_env[i] = str[0];
		}
		i++;
	}
	if (mini->tab_save_exp)
	{
		i = 0;
		while (mini->tab_save_exp[i])
		{
			str = ft_split(mini->tab_save_exp[i], '=');
			if (strcmp(str[0], "PWD") == 0)
			{
				str[0] = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
				mini->tab_save_exp[i] = str[0];
			}
			i++;
		}
	}
}

int	search_path_in_env(t_shell *mini, int a)
{
	int i;
	char **str;

	i = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(str[0], "HOME") == 0)
		{
			if (a == 2)
				ft_putstr_fd(str[1], 1);
			else
				chdir(str[1]);
			return 1;
		}
		i++;
	}
	if (mini->tab_save_exp)
	{
		i = 0;
		while (mini->tab_save_exp[i])
		{
			str = ft_split(mini->tab_save_exp[i], '=');
			if (strcmp(str[0], "HOME") == 0)
			{
				if (a == 2)
					ft_putstr_fd(str[1], 1);
				else
					chdir(str[1]);
				return 1;
			}
			i++;
		}
	}
	return 0;
}

void    ft_cd(char *path, t_shell *mini)
{
	int a;
	static int d;
	char buff[256];

	if (d == 0)
		mini->save_pwd = strdup(getcwd(buff, sizeof(buff)));
	else
	{
		mini->save_old_pwd = strdup(mini->save_pwd);
		if (getcwd(buff, sizeof(buff)) != NULL)
			mini->save_pwd = strdup(getcwd(buff, sizeof(buff)));
	}
	if (!path)
	{
		if (go_home(mini) == 0)
		{
			printf("minishell: cd: HOME not set\n");
			status_exec_g = 1;
		}
		else
		{
			search_path_in_env(mini, 1);
			change_pwd(mini);
			d++;
		}
	}
	else if (strcmp(path, "~") == 0)
	{
		if (go_home(mini) == 0)
		{
			if (search_path_in_env(mini, 1) == 0)
				chdir("/Users/otmallah");
		}
		change_pwd(mini);
		d++;
	}
	else if (strcmp(path, "-") == 0)
	{
		if (d == 0)
		{
			printf("cd: OLDPWD not set\n");
			status_exec_g = 1;
		}
		else
		{
			printf("%s\n", mini->save_old_pwd);
			chdir(mini->save_old_pwd);
			change_pwd(mini);
		}
	}
	else if (path[0] == '~' && path[1] == '/')
	{
		path = ft_strjoin("/", ft_strchr(path, '/'));
		chdir(path);
		change_pwd(mini);
		d++;
	}
	else if (path[0] == '$')
	{
		if (search_path_in_env(mini, 1) == 0)
			perror(NULL);
		d++;
	}
	else if (path)
	{
		a = chdir(path);
		if (a != 0)
			perror(NULL);
		d++;
		change_pwd(mini);
	}
}
