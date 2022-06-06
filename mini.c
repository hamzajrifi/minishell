/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:17 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/05 16:45:45 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

lexer_t *init_lexer(char *src)
{
    lexer_t *lexer ;
    
    lexer = malloc(sizeof(lexer_t));
    
    lexer->src = src;
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return (lexer);
}

void    lexer_advance(lexer_t *lexer)
{
    if (lexer->c && lexer->i < ft_strlen(lexer->src))
    {
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
}

void    lexer_skip_whitespace(lexer_t *lexer)
{
    while(lexer->c == ' ')
        lexer_advance(lexer);
}


token_t *lexer_get_next_token(lexer_t *lexer)
{
    while (lexer->c && lexer->i < ft_strlen(lexer->src))
    {
        if (lexer->c == ' ')
            lexer_skip_whitespace(lexer);
        if (lexer->c == '\'' || lexer->c == '"')
            return (lexer_collect_string(lexer));
		else if (lexer->c == '|' && lexer->src[lexer->i + 1] == '|')
        {
            lexer_advance(lexer);
			lexer_advance(lexer);
           	return (init_token(t_error, NULL));
            // return (lexer_advance_with_token(lexer , init_token(t_or, ft_strdup("||"))));
        }
        else if (lexer->c == '|')
        {
            int i = lexer->i + 1;
            while (lexer->src[i] == ' ')// error [  |  ]
                i++;
           	if(!lexer->src[i]  || lexer->src[i] == '|')
			{
            	lexer_skip_whitespace(lexer);
				lexer_advance(lexer);
           	    return (init_token(t_error, NULL));
			}
            return (lexer_advance_with_token(lexer, init_token(t_pip, lexer_get_current_char_as_string(lexer))));
        }
        else if (lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
        {
            lexer_advance(lexer);
            return (lexer_advance_with_token(lexer, init_token(t_heredoc, ft_strdup("<<"))));
        }
        else if (lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
        {
            lexer_advance(lexer);
            return (lexer_advance_with_token(lexer, init_token(t_append, ft_strdup(">>"))));
        }
        else if (lexer->c == '&' && lexer->src[lexer->i + 1] == '&')
        {
            lexer_advance(lexer);
			lexer_advance(lexer);
           	return (init_token(t_error, NULL));
            // return (lexer_advance_with_token(lexer , init_token(t_and, ft_strdup("&&"))));
        }
        else if (lexer->c == '>')
            return (lexer_advance_with_token(lexer , init_token(t_input, lexer_get_current_char_as_string(lexer))));
        else if (lexer->c == '<')
            return (lexer_advance_with_token(lexer , init_token(t_output, lexer_get_current_char_as_string(lexer))));
        else if (lexer->c)
            return (lexer_collect_arg(lexer));
        lexer_advance(lexer);
    }
    return (NULL);
}

token_t *init_token(int t_type, char *value)
{
    token_t *token ;
    
    token = malloc(sizeof(token_t));
    token->type = t_type;
    token->val = value;
    return (token);
}

token_t *lexer_advance_with_token(lexer_t *lexer, token_t *token)
{
    lexer_advance(lexer);
    return (token);
}

char	*check_var(lexer_t *lexer)
{
	char    *tmp;
    char    *str;

	str = NULL;
	lexer_advance(lexer);
	if (lexer->c == '\0' || lexer->c == ' ' || lexer->c == '|' || lexer->c == '=')
		return (ft_strdup("$"));
    else if ((lexer->c >= '0' && lexer->c <= '9') || lexer->c == '*')
    {
		lexer_advance(lexer);
	    return (ft_strdup(""));
	}
	else
	{
		while (lexer->c != '\0' && lexer->c != '\\' 
            && lexer->c != ' ' && lexer->c != '$' && lexer->c != '|' 
            && lexer->c != '"' && lexer->c != '\''  && lexer->c != '='
			)
		{
			tmp = lexer_get_current_char_as_string(lexer);
			str = ft_strjoin(str, tmp);
        	free(tmp);
        	lexer_advance(lexer);
		}
		if (getenv(str))
			return (getenv(str));
		else 
			return (ft_strdup(""));
	}
	return (str);
}

int    check_lexer_c(char c)
{
    if (c != ' ' && c != '<' && c != '>' &&  c != '|' && c != '"' && c != '\'')
        return (1);
    return (0);
}

void    check_backslash(lexer_t **lexer)
{
    char    c;
    char    k;

    c = (*lexer)->c;
    k = (*lexer)->src[(*lexer)->i + 1];
    if (c == '\\' && (k == '\\' || k == ';' || k == '"' || k == '\'' || k == '$' || k == '>' || k == '<'))
        lexer_advance(*lexer);
}

token_t *lexer_collect_string(lexer_t *lexer)
{
    char    *tmp;
    char    *str;
    char    c;
    
    c = lexer->c;
    lexer_advance(lexer);
    str = NULL;
    if (lexer->c == c && (lexer->src[lexer->i + 1] == '\0' || lexer->src[lexer->i + 1] == ' '))
    {
        lexer_advance(lexer);
        return (init_token(t_args, ft_strdup("")));
    }
    while(lexer->c && lexer->c != c)
    {
        if (lexer->c == '$' && c == '"')
        	str = ft_strjoin(str, check_var(lexer));
        else
        {
            check_backslash(&lexer);
            tmp = lexer_get_current_char_as_string(lexer);
            str = ft_strjoin(str, tmp);
            free(tmp);
            lexer_advance(lexer);
        }
    }
    if (!lexer->c) // error [']
        return (init_token(t_error, NULL));
    lexer_advance(lexer);
    if (check_lexer_c(lexer->c))
        str = ft_strjoin(str, (lexer_collect_arg(lexer))->val);
    else if (lexer->c == '\'' || lexer->c == '"')
        str = ft_strjoin(str, (lexer_collect_string(lexer))->val);
    return (init_token(t_args, str));
}

token_t *lexer_collect_arg(lexer_t *lexer)
{
    char    *tmp;
    char    *str;

    str = NULL;
    while(lexer->src[lexer->i] && lexer->c != ' ' && lexer->c != '|' && lexer->c != '>' && lexer->c != '<')
    {
		if (lexer->c == '$')
        	str = ft_strjoin(str, check_var(lexer));
        else
		{
            check_backslash(&lexer);
			tmp = lexer_get_current_char_as_string(lexer);
        	str = ft_strjoin(str, tmp);
        	free(tmp);
        	lexer_advance(lexer);
        	while (lexer->c == '"' ||lexer->c == '\'')
                str = ft_strjoin(str, (lexer_collect_string(lexer))->val);
		}
    }
    return (init_token(t_args, str));
}

char *lexer_get_current_char_as_string(lexer_t *lexer)
{
    char    *str;
    
    str = malloc(sizeof(char) * 2);
    str[0] = lexer->c;
    str[1] = '\0'; 
    return (str);
}