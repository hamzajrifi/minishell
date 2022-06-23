/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <hjrifi@student.42.fr>          	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:12 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/14 17:34:31 by hjrifi	          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_type_value(char *str, int type)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '*')
			return (t_wildcard);
	}
	return (type);
}

t_list	*ft_check_parser(t_token **token, t_lexer *lexer,
t_list *lst, t_list *head)
{
	int	i;

	i = 1;
	*token = lexer_get_next_token(lexer, *token);
	while (*token && (*token)->e_type == t_args)
	{
		lst->val = ft_realloc_char(lst->val);
		lst->v_type = ft_realloc_int(lst->v_type, lst->val);
		lst->val[i] = ft_strdup((*token)->val);
		lst->v_type[i] = check_type_value((*token)->val, (*token)->e_type);
		i++;
		free((*token)->val);
		*token = lexer_get_next_token(lexer, *token);
	}
	if (i > 1 && lst->v_type[0] == 3)
		lst->v_type[1] = t_end;
	else if (i > 1 && lst->v_type[0] == t_output)
		lst->v_type[1] = t_file;
	if ((*token) && (*token)->e_type == t_error)
		return (NULL);
	return (lst);
}

int	is_string_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

t_list	*ft_parser_second(t_lexer *lexer, t_token *token,
t_list *lst, t_list *head)
{
	while (token && token->e_type != t_error)
	{
		lst = ft_check_parser(&token, lexer, lst, head);
		if (!lst)
			return (print_error(" 003", lexer, token, head));
		if (token && lst)
		{
			lst = add_node_in_lst(token->val, token->e_type, head);
			if (!lst)
				return (print_error(" 001", lexer, token, head));
			if (token->e_type > t_output && token->e_type <= t_error)
			{
				token = lexer_get_next_token(lexer, token);
				lst = add_node_in_lst(token->val, token->e_type, head);
				if (!lst || token->e_type == t_error)
					return (print_error(" 002", lexer, token, head));
			}
			while (lst->next)
				lst = lst->next;
		}
	}
	return (head);
}

char	*delet_parenthese(char *str)
{
	char	*tmp;
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')')
			n++;
		i++;
	}
	tmp = malloc(sizeof(char) * n + 1);
	i = 0;
	n = 0;
	while (str[i])
	{
		if(str[i] != '(' && str[i] != ')')
			tmp[n++] = str[i];
		i++;
	}
	tmp[n] = '\0';
	free(str);
	str = tmp;
	return (tmp);
}

char	*check_parenthese(char *str)
{
	int		i;
	int		n;
	char	tab[ft_strlen(str)];

	i = 0;
	n = 0;
	tab[0] = '\0';
	while(str[i] && n >= 0)
	{
		if(str[i] == '(' && str[i + 1] == ')')
			return (NULL);
		else if(str[i] == '(')
			tab[n++] = '(';
		else if (str[i] == ')')
		{
			if (!tab[--n])
				return (NULL);
			else if (tab[n] == '(')
				tab[n] = '\0';
		}
		i++;
	}
	if (n != 0 || (!str[i] && tab[n] == '('))
		return (NULL);
	str = delet_parenthese(str);
	printf("str here = %s\n", str);
	return (str);
}

t_list	*ft_parser(char *src, t_shell *mini)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*lst;
	t_list	*head;

	token = NULL;
	lst = NULL;
	if (is_string_empty(src))
		return (NULL);
	src = check_parenthese(src);
	if (!src)
		return (print_error(" 0000", lexer, token, lst));
	lexer = init_lexer(src, mini);
	token = lexer_get_next_token(lexer, token);
	if (token)
		lst = add_node_in_lst(token->val, token->e_type, lst);
	if (token && token->e_type == t_error)
		return (print_error(" 000", lexer, token, lst));
	head = lst;
	lst = ft_parser_second(lexer, token, lst, head);
	if (!lst)
		return (NULL);
	free(lexer);
	return (head);
}
