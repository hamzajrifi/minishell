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
	int		is_dqt;
	int		is_sqt;
	int		i;
	char	*tmp;

	pip = NULL;
	is_dqt = 0;
	is_sqt = 0;
	i = 0;
	
	while(src->str[i])
	{
		while(src->str[i] && src->str[i] == '"' )
		{
			i++;
			is_dqt++;
			while (src->str[i] && src->str[i] != '"')
				i++;
			if (src->str[i] && src->str[i] == '"')
				is_dqt++;
			i++;
		}
		while(src->str[i] && src->str[i] == '\'')
		{
			i++;
			is_sqt++;
			while (src->str[i] && src->str[i] != '\'')
				i++;
			if (src->str[i] && src->str[i] == '\'')
				is_sqt++;
			i++;
		}
		if ((src->str[i] == '|' || src->str[i + 1] == '\0' || src->str[i] == '\0' ))
		{
			if(src->str[i + 1] == '\0')
				i++;
			tmp = malloc(sizeof(char) * (i - src->end) + 1);
			src->i = 0;
			while (src->i + src->end < i )
				tmp[src->i++] = src->str[src->end + src->i];
			src->end = i + 1;
			tmp[src->i] = '\0';
			pip = add_node_pip(tmp , pip);
			free(tmp);	
		}
		if ( src->str[i] != '\'' && src->str[i] != '"')
			i++;
	}
	if (is_dqt % 2 != 0 || is_sqt % 2 != 0)
		printf("error s_qt or d_qt\n");
	return (pip);
}

s_pipes	*check_node(s_pipes *pip)
{
	int		i;
	int		is_scl; /// is semicolon

	is_scl = 0;
	
	while (pip)
	{
		i = 0;
		while (pip->prt[i])
		{
			//printf("pip->prt = %c\n", pip->prt[i]);
			i++;
		}
		pip = pip->next;
	}
	
	return (pip);
}

void	minishell(char *str)
{
	t_contents	src;
	s_pipes		*pip ;
	s_pipes		*head ;

	src.str = str;
	src.i = 0;
	src.end = 0;
	pip = split_pipe(&src);
	check_node(pip);
	head = pip;
	//splite_cmd();
	while (head)
	{
		printf("tmp = %s\n", head->prt);
		head = head->next;
	}
	
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
		add_history(line);
			free(line);
		i = 0;
	}
	return (0);
}