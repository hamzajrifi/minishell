/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:57:56 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/23 22:44:11 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "sec_parsing/header/minishell.h"

void	handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && id != 0)
	{
		if (sig == SIGQUIT)
			write(1, "Quit: 3\n", 9);
		kill(id, sig);
		g_status_exec = 130;
	}
	else if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_status_exec = 1;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\r", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	id = 0;
}

int	finde_her(t_list *lis)
{
	while (lis)
	{
		if (lis->v_type[0] == 11)
			return (1);
		lis = lis->next;
	}
	return (0);
}

int	ft_findwild(t_list *list)
{
	while (list && list->v_type[0] != 11)
	{
		if (list->val[1])
		{
			if (list->v_type[1] == 15)
				return (1);
		}
		list = list->next;
	}
}

int	finder_red(t_list *list)
{
	while (list)
	{
		if (list && (list->v_type[0] == 6 || list->v_type[0] == 4))
			return (2);
		else if (list && list->v_type[0] == 8)
			return (3);
		else if (list && list->v_type[0] == 3)
			return (4);
		list = list->next;
	}
	return (0);
}

void	ft_mini(t_shell *mini, char *src)
{
	t_list	*lst;
	t_list	*head;

	lst = ft_parser(src, mini);
	system("leaks minishell");

	// printf("outsid\n");
	//while (lst)
	//{
	//	int i = -1;
	//	while (lst->val && lst->val[++i])
	//		printf(" val = %s -- type = %d == ", lst->val[i], lst->v_type[i]);
	//	printf("\n");
	//	lst = lst->next;
	//}
	head = lst;
	if (!lst)
		return ;
	if (ft_findwild(lst) == 1)
		
	else if (finde_her(lst) == 1)
		pipes(mini, lst);
	else if (finder_red(lst) == 2)
		ft_redirection(mini, lst, 0, 1);
	else if (finder_red(lst) == 4)
		heredoc(mini, lst, 0, 1);
	else if (finder_red(lst) == 3)
		ft_redin(mini, lst, 1, 0);
	else
	{
		ft_exit_status(mini, lst);
		ft_check_built(mini, lst, 1);
	}
	ft_free_list(head);
}

int	main(int ac, char **av, char **env)
{
	char	*src;
	t_shell	mini;

	(void)ac;
	(void)av;
	mini.tab_save_env = env;
	mini.tab_save_exp = NULL;
	mini.counter = 0;
	mini.num_ofall_cmd = 0;
	mini.num_cmd = 0;
	mini.cnt = 0;
	mini.fs = 0;
	signal(SIGINT, handler);
	while (1337)
	{
		mini.counter = 0;
		src = readline("mimishell : ");
		if (errno == 13)
			g_status_exec = 126;
		if (src == NULL)
		{
			printf(" exit\n");
			exit(0);
		}
		ft_mini(&mini, src);
		add_history(src);
		free(src);
	}
	return (0);
}
