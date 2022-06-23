/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:15:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 21:52:21 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	chdi(t_shell *mini, char *path);
void	old(t_shell *mini, int a);

char	**go_home2(t_shell *mini)
{
	int		i;
	int		k;
	int		j;
	char	**temp;

	j = 0;
	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(temp[0], "HOME") == 0)
			return (temp);
		ft_free(temp);
		j = 0;
		i++;
	}
	return (0);
}

void	home(t_shell *mini)
{
	char	**str;
	int		i;

	i = 0;
	str = go_home2(mini);
	system("leaks minishell");
	if (str[1] != NULL)
	{
		chdir(str[1]);
		ft_free(str);
	}
	change_pwd(mini);
	mini->built++;
}

void	sec_home(t_shell *mini, char *path)
{
	path = ft_strjoin("/", ft_strchr(path, '/'));
	chdir(path);
	change_pwd(mini);
	mini->built++;
}

void	hh(t_shell *mini)
{
	if (search_path_in_env(mini, 1) == 0)
		perror(NULL);
	mini->built++;
}

void	ft_cd(char *path, t_shell *mini)
{
	static int			a;
	char				buff[256];

	a = 0;
	if (mini->built == 0)
		mini->save_pwd = strdup(getcwd(buff, sizeof(buff)));
	else if (ft_strcmp(mini->save_pwd, getcwd(buff, sizeof(buff))) != 0)
		old(mini, a);
	if (path == NULL)
		unset_home(mini);
	else if (strcmp(path, "~") == 0)
		home(mini);
	else if (strcmp(path, "-") == 0)
		oldpwd_not_set(mini);
	else if (path[0] == '~' && path[1] == '/')
		sec_home(mini, path);
	else if (path[0] == '$')
		hh(mini);
	else if (path)
		chdi(mini, path);
	a++;
}
