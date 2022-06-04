/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:08:20 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/04 14:31:23 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void    ft_echo(t_shell *mini, char **str, int fd)
{
    int i;
    int j;
    int a;
    char *temp;

    i = 1;
    j = 0;
    a = 1;
    while (str[i])
    {
        if (strcmp(str[i], "-n") != 0)
        {
            if (strcmp(str[i], "$") == 0)
                ft_putstr_fd(str[i], fd);
            else if (strcmp(str[i], "$?") == 0)
            {
                ft_putstr_fd(ft_itoa(status_exec_g), fd);
                status_exec_g = 0;
            }
            else if (str[i][0] == '$')
            {
                while (mini->tab_save_env[j])
                {
                    temp = ft_substr(mini->tab_save_env[j], 0, len(mini->tab_save_env[j]));
                    if (strcmp(temp, ft_strchr(str[i], '$')) == 0)
                    {
                        ft_putstr_fd(ft_strchr(mini->tab_save_env[j], '='), fd);
                        break ;
                    }
                    j++;
                }
                if (mini->tab_save_exp)
                {
                    j = 0;
                    while (mini->tab_save_exp[j])
                    {
                        temp = ft_substr(mini->tab_save_exp[j], 0, len(mini->tab_save_exp[j]));
                        if (strcmp(temp, ft_strchr(str[i], '$')) == 0)
                        {
                            ft_putstr_fd(ft_strchr(mini->tab_save_exp[j], '='), fd);
                            break ;
                        }
                        j++;
                    }
                }
                j = 0;
            }
            else if (str[i][1] == 'n' && str[i][2] == 'n')
            {
                while (str[i][a])
                {
                    if (str[i][a] == 'n')
                        a++;
                    else
                    {
                        a = 1000;
                        ft_putstr_fd(str[i], fd);
                        break;
                    }
                }
            }
            else if (strcmp(str[i], "~") == 0)
                search_path_in_env(mini, 2);
            else
            {
                ft_putstr_fd(str[i], fd);
                if (str[i + 1] != NULL)
                    write(fd, " ", 1);
            }
        }
        i++;
    }
    if (strcmp(str[1], "-n") != 0)
        ft_putstr_fd("\n", fd);
}