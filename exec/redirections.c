/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:24:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/04 15:14:51 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int     open_all_files(t_list *list)
{
    int fd;

    while (list)
    {
        if (list->v_type[0] == 6)
            fd = open(list->val[1], O_CREAT | O_RDWR | O_TRUNC , 0644);
        list = list->next;
    }
    return fd;
}

void    ft_redirection(t_shell *mini, t_list *lst)
{
    int fd;
    int id;

    fd = open_all_files(lst);
    id = fork();
    if (id == 0)
    {
        dup2(fd, STDOUT_FILENO);
        ft_check_built(mini, lst, fd);
        exit(0);
    }
    close(fd);
    wait(NULL);
}
