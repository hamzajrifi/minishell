/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:07:33 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/13 13:51:45 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int size_vl(char **str)
{
	int i = 0;

	while (str[i])
		i++;
	return i;
}

void    ft_check_built(t_shell *mini, t_list *lst, int fd)
{
    int wstatus;

    if (lst->val && lst->v_type[0] == 1)
    {
        if (strcmp(lst->val[0], "export") == 0)
        {
            if (lst && size_vl(lst->val) > 1)
				ft_print_export(mini, lst->val, 1);
            else
                ft_print_export(mini, NULL, 1);
        }
        else if (strcmp(lst->val[0], "pwd") == 0)
            ft_pwd(fd);
        else if (strcmp(lst->val[0], "env") == 0)
            ft_env(mini, fd);
        else if (strcmp(lst->val[0], "exit") == 0)
        {
            if (lst->val[1] != NULL && lst->v_type[1] != 0)
                ft_exit(lst->val[1], fd);
            else
                ft_exit(NULL, fd);
        }
        else if (strcmp(lst->val[0], "unset") == 0)
        {
            if (lst && lst->val[1] != NULL)
                ft_unset(mini, lst->val, fd);
        }
        else if (strcmp(lst->val[0], "cd") == 0)
        {
            if (lst->val[1] != NULL)
                ft_cd(lst->val[1], mini);
            else
                ft_cd(NULL, mini);
        }
		else if (ft_strcmp(lst->val[0], "echo") == 0)
			ft_echo(mini, lst->val, fd);
        else
        {
            if (fork() == 0)
				exec_cmd(mini, lst);
			else
			{
				wait(&wstatus);
				if (WIFEXITED(wstatus))
				{
					status_exec_g = WEXITSTATUS(wstatus);
					if (status_exec_g == 1)
						status_exec_g = 127;
                }
            }
        }
    }
}

int find(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			return 1;
		i++;
	}
	return 0;
}

void	exec_cmd(t_shell *mini, t_list *lst)
{
	char **temp = NULL;
	char *str = NULL;
	int i;
	int size;

	i = 0;
	if (lst->val[0][0] == '.' || lst->val[0][0] == '/')
		ft_check_cmd(mini, lst);
	else if (check_path_if_exi(mini) != NULL)
	{
		str = check_path_if_exi(mini);
		if (str != NULL)
		{
			if (find(str) == 1)
				temp = ft_split(str, ':');
			else
			{
				temp = (char **)malloc(sizeof(char *) * 2);
				temp[i] = str;
				temp[i + 1] = NULL;
			}
			while (temp[i])
			{
				size = ft_strlen(temp[i]);
				temp[i] = ft_strjoin(temp[i], "/");
				str = ft_strjoin(temp[i], lst->val[0]);
				if (access(str, F_OK) == 0)
					execve(str, &lst->val[0], mini->tab_save_env);
				i++;
			}
			write(2, lst->val[0], ft_strlen(lst->val[0]));
			write (2, " :command not found\n", 20);
			exit(0);
		}
	}
	else
	{
		write(2, lst->val[0], ft_strlen(lst->val[0]));
		write (2, " :command not3found\n", 20);
		exit(0);
	}
}

void	ft_check_cmd(t_shell *mini, t_list *lst)
{
	if (lst->val[0][0] == '.')
	{
		if (access(lst->val[0], F_OK | X_OK) == 0)
		{
			execve(lst->val[0], &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		write (2, lst->val[0], ft_strlen(lst->val[0]));
		write (2, " :no such file or directory\n", 29);
		exit(127);
	}
	else if (lst->val[0][0] == '/')
	{
		if (access(lst->val[0], F_OK) == 0)
		{
			execve(lst->val[0], &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		write (2, lst->val[0], ft_strlen(lst->val[0]));
		write (2, " :command not found \n", 22);
		exit(0);
	}
}	



char	*check_path_if_exi(t_shell *mini)
{
	int i;
	char	*temp;

	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_substr(mini->tab_save_env[i], 0, len(mini->tab_save_env[i]));
		if (strcmp(temp, "PATH") == 0)
		{
			return (ft_strchr(mini->tab_save_env[i],'='));
		}
		i++;
	}
	if (mini->tab_save_exp && mini->tab_save_exp[0] != NULL)
	{
		i = 0;
		temp = ft_substr(mini->tab_save_exp[i], 0, len(mini->tab_save_exp[i]));
		if (strcmp(temp, "PATH") == 0)
		{
			return (ft_strchr(mini->tab_save_exp[i],'='));
		}
		i++;
	}
	return NULL;
}