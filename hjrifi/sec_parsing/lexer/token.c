/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:48:55 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/19 19:48:56 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*init_token(int t_type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->e_type = t_type;
	if (value)
	{
		token->val = ft_strdup(value);
		if (value)
			free(value);
	}
	else
		token->val = NULL;
	return (token);
}

t_token	*lexer_get_next_or_and_arg(t_lexer *lexer)
{
	if (lexer->c == '&' && lexer->src[lexer->i + 1] == '&')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_token(t_and, ft_strdup("&&")));
	}
	else if (lexer->c == '|' && lexer->src[lexer->i + 1] == '|')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_token(t_or, ft_strdup("||")));
	}
	else if (lexer->c)
		return (lexer_collect_arg(lexer));
	return (NULL);
}

t_token	*lexer_get_next_token_second(t_lexer *lexer, t_token *token)
{
	if (lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token
			(lexer, init_token(t_append, ft_strdup(">>"))));
	}
	else if (lexer->c == '>')
		return (lexer_advance_with_token(lexer, init_token
				(t_input, lexer_get_current_char_as_string(lexer))));
	else if (lexer->c == '<')
		return (lexer_advance_with_token(lexer, init_token
				(t_output, lexer_get_current_char_as_string(lexer))));
	else
		return (lexer_get_next_or_and_arg(lexer));
	return (NULL);
}

void	ft_check_arg_wildcard(t_lexer *lexer, t_token *token, int i)
{
	char	*tmp;

	while (check_lexer_c(lexer->c) && lexer->c != '*')
	{
		tmp = lexer_get_current_char_as_string(lexer);
		token->tab[i] = ft_h_strjoin(token->tab[i], tmp);
		free(tmp);
		lexer_advance(lexer);	
	}
	token->val = ft_h_strjoin(ft_strdup("*"), token->tab[i]);
	free(token->tab[i]);
}

t_token *lexer_collect_wildcard(t_lexer *lexer)
{
	t_token *token;
	int		i;

	i = 2;
	token = malloc(sizeof(t_token));
	token->tab = malloc(sizeof(char *) * 2);
	token->tab[0] = ft_strdup("*");
	token->tab[1] = NULL;
	lexer_advance(lexer);
	while (lexer->c == '*')
		lexer_advance(lexer);
	while (lexer->c == '"')
	{
		token->tab = ft_realloc_char(token->tab);
		token->tab[i] = lexer_collect_string(lexer)->val; 
		if (!token->tab[i++])
			return (NULL);
	}
	token->e_type = t_wildcard;
	ft_check_arg_wildcard(lexer, token, i);
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer, t_token *token)
{
	if (token)
		free(token);
	while (lexer->c && lexer->i < ft_strlen(lexer->src))
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		//if (ft_error(lexer))
		//	return (init_token(t_error, NULL));
		else if (lexer->c == '*')
			return (lexer_collect_wildcard(lexer));
		else if (lexer->c == '\'' || lexer->c == '"')
			return (lexer_collect_string(lexer));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token
					(t_pip, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
		{
			lexer_advance(lexer);
			return (lexer_advance_with_token
				(lexer, init_token(t_heredoc, ft_strdup("<<"))));
		}
		else if (lexer->c)
			return (lexer_get_next_token_second(lexer, token));
	}
	return (NULL);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}
