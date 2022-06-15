/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:52:40 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/09 12:39:14 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char    *ft_getenv(t_shell *mini, char *str)
{
    int j;
    int i;
    char *temp;
    
    i = 0;
    j = 0;
    while (mini->tab_save_env[j])
    {
        temp = ft_substr(mini->tab_save_env[j], 0, len(mini->tab_save_env[j]));
        if (strcmp(temp, str) == 0)
        {
            return (ft_strchr(mini->tab_save_env[j], '='));
        }
        j++;
    }
    if (mini->tab_save_exp)
    {
        j = 0;
        while (mini->tab_save_exp[j])
        {
            temp = ft_substr(mini->tab_save_exp[j], 0, len(mini->tab_save_exp[j]));
            if (strcmp(temp, str) == 0)
            {
                return (ft_strchr(mini->tab_save_exp[j], '='));
            }
            j++;
        }
    }
    return NULL;
}