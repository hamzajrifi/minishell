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
		puts("987");
		ft_exit_status(mini, list);
		id = fork();
		if (id == 0)
		{
			ft_check_built(mini, list, 1);
			exit(0);
		}
		wait(NULL);
		if (g_id.failer == 2)
		{
			g_id.failer = 0;
			break ;
		}
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
		puts("321");
		ft_exit_status(mini, list);
		id = fork();
		if (id == 0)
		{
			ft_check_built(mini, list, 1);
			exit(0);
		}
		wait(NULL);
		if (g_id.failer != 2)
		{
			g_id.failer = 0;
			break ;
		}
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
	int i = 0;
	while (list)
	{
		ft_exit_status(mini, list);
		if (i == 0)
		{
			exec_bonus(mini, list);
			if (list->next)
				list = list->next->next;
			else
			{
				list = list->next;
			}
		}
		if (list->next && list->next->v_type[0] == 13 && g_id.failer == 2)
		{
			printf("lst2 = %s\n", list->val[0]);
			exec_bonus(mini, list);
		}
		else if (g_id.failer != 2)
		{
			printf("lst2 = %s\n", list->val[0]);
			exec_bonus(mini, list);
		}
		if (list->next)
			list = list->next->next;
		else
		{
			list = list->next;
		}
		i++;
	}
}
