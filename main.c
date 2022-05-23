#include "header/minishell.h"
#include <string.h>

/// handel signal
void checksignal(int nbr)
{
	if (nbr == SIGINT)
		exit(1);
}
///

/// ft_strlen
int	ft_strlen(char *str)
{
	int	i;

	i = 0 ;
	while (str[i])
		i++;
	return (i);
}
///

/// ft_strdub 
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		len_s1;

	len_s1 = ft_strlen((char *)s1);
	i = 0;
	ptr = (char *)malloc(len_s1 * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
////

s_pipes *add_node_pip(char *str, s_pipes *pip)
{
	s_pipes *new;
	s_pipes	*head;

	head = pip;
	new = malloc(sizeof(s_pipes));
	new->prt = ft_strdup(str);
	new->next = NULL;
	if(pip)
	{
		while (pip->next)
			pip = pip->next;
		pip->next = new;
	}
	else
		head = new;
	return (head);
}

///// free node 
void	free_node(s_pipes *pip)
{
	s_pipes *tmp;
	s_pipes *head;
	
	tmp = pip;
	head = pip;
	while(pip)
	{
		free(pip->prt);
		pip = pip->next;
		free(tmp);
		tmp = pip;
	}
	free(tmp);
	head = NULL;
}
///

s_pipes	*split_pipe( t_contents *src)
{
	s_pipes	*pip;
	int		is_scln;
	int		i;
	char	*tmp;

	pip = NULL;
	is_scln = 0;
	i = 0;
	while(src->str[i] && src->i == 0)
	{
		if (src->str[i] == '"')
			is_scln += 1;
		if ((is_scln % 2 == 0 && src->str[i] == '|') )
		{
			tmp = malloc(sizeof(char) * i  + 1);
			src->i = 0;
			while (src->i < i )
				tmp[src->i++] = src->str[src->end + src->i];
			src->end = i + 1;
		 	tmp[src->i] = '\0';
		 	pip = add_node_pip(tmp , pip);
		 	free(tmp);
		}
		i++;
	}
	if (!pip && is_scln % 2 == 0)
		pip = add_node_pip(ft_strdup(src->str) , pip);
	while(src->str[i] && src->end != 0)
	{
		if (src->str[i] == '"')
			is_scln += 1;
		if (is_scln % 2 == 0 && src->str[i] == '|')
		{
			tmp = malloc(sizeof(char) * (i - src->end) + 1);
			src->i = 0;
			while (src->i < i && (src->str[src->i + src->end] != '|' || (src->str[src->i + src->end] == '|' && is_scln % 2 != 0)))
			{
				if (src->str[src->i + src->end] == '"')
					is_scln += 1;
				tmp[src->i++] = src->str[src->end + src->i];
			}
			src->end = i + 1;
			tmp[src->i] = '\0';
			pip = add_node_pip(tmp , pip);
			free(tmp);	
		}
		else if (src->str[i + 1] == '\0')
		{
			i += 1;
			tmp = malloc(sizeof(char) * (i - src->end) + 1);
			src->i = 0;
			while (src->str[src->end + src->i])
				tmp[src->i++] = src->str[src->end + src->i];
			tmp[src->i] = '\0';
			pip = add_node_pip(tmp , pip);
			free(tmp);	
		}
		i++;
	}
	return (pip);
}


void	minishell(char *str)
{
	t_contents src;
	s_pipes *pip ;

	src.str = str;
	src.i = 0;
	src.end = 0;
	pip = split_pipe(&src);
	//splite_cmd();
	
	free_node(pip);
}

//// main
int main()
{
	int		i = 0;

	signal(SIGINT, checksignal);
	while (1)
	{
		char *line = readline("minishell>");
		minishell(line);
			free(line);
		i = 0;
	}
	return (0);
}