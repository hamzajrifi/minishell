/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:13:02 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 02:17:46 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_and(t_list *list, t_shell *mini)
{
	int id;
	int wstatus;

	while (list && list->v_type[0] != 12)
	{
		ft_exit_status(mini, list);
		id = fork();
		if (id == 0)
		{
			ft_check_built(mini, list, 1);
			exit(0);
		}
		wait(NULL);
		if (failer == 2)
			break;
		if (list->next)
			list = list->next->next;
		else
			list = list->next;
	}
}

void	ft_or(t_list *list, t_shell *mini)
{
	int id;
	int wstatus;

	while (list && list->v_type[0] != 13)
	{
		ft_exit_status(mini, list);
		id = fork();
		if (id == 0)
		{
			ft_check_built(mini, list, 1);
			exit(0);
		}
		wait(NULL);
		if (failer != 2)
			break;
		if (list->next)
			list = list->next->next;
		else
			list = list->next;
	}
}

void	exec_both_and_or(t_list *list, t_shell *mini)
{
	int id;
	int wstatus;

	while (list)
	{
		ft_exit_status(mini, list);
		id = fork();
		if (id == 0)
		{
			ft_check_built(mini, list, 1);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
		if (list->next && list->next->v_type[0] == 12)
		{
			while (list && list->next && list->next->v_type[0] == 12)
				list = list->next->next;
			if (list->next)	
				list = list->next->next;
			else 
				list = list->next;
		}
		else
		{
			if (list->next)
				list = list->next->next;
			else
				list = list->next;
		}
	}
	
}