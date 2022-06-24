/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_both.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:37:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/05/26 17:15:48 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int salam(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '&' && str[i + 1] == '&')
            return 1;
        i++;
    }
    return 0;
}

void    ft_both(t_shell *mini, char *str)
{
    char **tab;
    int i;

    i = 0;
    tab = ft_split(str, '|');
    while (tab[i])
    {
        if (salam(tab[i]) == 1)
            ft_and_bonus(mini, tab[i]);
        else
            ft_or_bonus(mini, tab[i]);
        i++;
    }
}