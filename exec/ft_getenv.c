/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:52:40 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/05 21:02:48 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char    *ft_getenv(t_shell *mini, char **str, int fd)
{
    int j;
    int i;
    char *temp;
    
    i = 0;
    j = 0;
    while (mini->tab_save_env[j])
    {
        temp = ft_substr(mini->tab_save_env[j], 0, len(mini->tab_save_env[j]));
        if (strcmp(temp, ft_strchr(str[i], '$')) == 0)
        {
            //ft_putstr_fd(ft_strchr(mini->tab_save_env[j], '='), fd);
            return (ft_strchr(mini->tab_save_env[j], '='));
            //break ;
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
                //ft_putstr_fd(, fd);
                return (ft_strchr(mini->tab_save_exp[j], '='));
                //break ;
            }
            j++;
        }
    }
    return NULL;
}