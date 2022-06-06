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
        write (fd, str[i], ft_strlen(str[i]));
        if (str[i + 1] != NULL)
            write(fd, " ", 1);
        i++;
    }
    if (strcmp(str[1], "-n") != 0)
        ft_putstr_fd("\n", fd);
}