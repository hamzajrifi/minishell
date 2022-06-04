/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:13:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/04 17:04:50 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void    heredoc(t_shell *mini, t_list *list)
{
    char *find;
    int fd;
    int out;

    out = 1;
    fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC , 0644);
    if (list->next->next && list->next->next->v_type[0] == 6)
        out = open_all_files(list->next->next); 
    while (1)
    {
        find = readline(">");
        if (find == NULL)
            break ;
        if (strcmp(find, list->next->val[1]) == 0)
            break;
        ft_putendl_fd(find, fd);
    }
    close(fd);
    fd = open("/tmp/test", O_CREAT | O_RDWR, 0644);
    if (fork() == 0)
    {
        dup2(fd, 0);
        dup2(out, 1);
        ft_check_built(mini, list, 1);
        exit(0);
    }
    close(fd);
    wait(NULL);
    unlink("/tmp/test");
}