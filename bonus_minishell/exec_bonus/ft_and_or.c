/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:13:02 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 09:13:53 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_and(t_list *list, t_shell *mini)
{
	int	id;

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
		if (g_id.failer == 2)
			break ;
		if (list->next)
			list = list->next->next;
		else
			list = list->next;
		g_id.failer = 0;
	}
}

void	ft_or(t_list *list, t_shell *mini)
{
	int	id;

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
		if (g_id.failer != 2)
			break ;
		if (list->next)
			list = list->next->next;
		else
			list = list->next;
		g_id.failer = 0;
	}
}

void	exec_bonus(t_shell *mini, t_list *list)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		ft_check_built(mini, list, 1);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

void	counter_list(t_list **list)
{
	if ((*list)->next)
		*list = (*list)->next->next;
	else
		*list = (*list)->next;
}

void	exec_both_and_or(t_list *list, t_shell *mini)
{
	while (list)
	{
		ft_exit_status(mini, list);
		exec_bonus(mini, list);
		if (list->next && list->next->v_type[0] == 12)
		{
			while (list && list->next && list->next->v_type[0] == 12
				&& g_id.failer != 2)
				list = list->next->next;
			if (list->next)
				list = list->next->next;
			else
				list = list->next;
			printf("lst = %s\n", list->val[0]);
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
