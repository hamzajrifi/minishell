/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:57:56 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/24 09:11:58 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "sec_parsing/header/minishell.h"

void	handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g_id.id != 0)
	{
		if (sig == SIGQUIT)
			write (1, "Quit: 3\n", 9);
		kill(g_id.id, sig);
	}
	else if (g_id.cheecker != 0)
		close(0);
	else if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_id.g_status_exec = 1;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\r", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_id.cheecker = 0;
	g_id.id = 0;
}

void	ft_mini(t_shell *mini, char *src)
{
	t_list	*lst;
	t_list	*head;

	lst = ft_parser(src, mini);
	head = lst;
	if (!lst)
		return ;
	if (find_both_and_or(lst) == 1)
		exec_both_and_or(lst, mini);
	else if (ft_findwild(lst) == 1)
		ft_wildcards(&lst, mini);
	else if (ft_findwild(lst) == 2)
		ft_and(lst, mini);
	else if (ft_findwild(lst) == 3)
		ft_or(lst, mini);
	else if (finde_her(lst) == 1)
		pipes(mini, lst);
	else
		ft_mini_second(mini, lst);
	//ft_free_list(head);
}

void	initialiation_mini(t_shell *mini, char **env)
{
	mini->tab_save_env = env;
	mini->tab_save_exp = NULL;
	mini->counter = 0;
	mini->num_ofall_cmd = 0;
	mini->num_cmd = 0;
	mini->cnt = 0;
	mini->fs = 0;
	mini->built = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*src;
	t_shell	mini;

	(void)ac;
	(void)av;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	initialiation_mini(&mini, env);
	while (1337)
	{
		mini.counter = 0;
		g_id.g_fd = dup(0);
		src = readline("mimishell : ");
		if (errno == 13)
			g_id.g_status_exec = 126;
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
