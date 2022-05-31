/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <hjrifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:12 by hjrifi            #+#    #+#             */
/*   Updated: 2022/05/31 13:20:35 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

t_list *add_node_in_lst(char *str, int v_type, t_list *lst)
{
	t_list *new;
	t_list	*head;
   
	head = lst;
    if (v_type == t_args || v_type == t_string)
    {        
        v_type = 1;
    }
	new = malloc(sizeof(t_list));
    new->val = malloc (sizeof(char*) * 3);
    new->v_type = malloc(sizeof(int) * 2);
	new->val[0] = str;
    new->val[3] = NULL;
    new->v_type[0] = v_type;
	new->next = NULL;
	if(lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	else
		head = new;
	return (head);
}

// t_list  *ft_check_herdoc(token_t *token, lexer_t *lexer)
// {
    
//     return (lst);
// }

t_list  *ft_parser(char *src)
{
    lexer_t *lexer;
    token_t *token;
    t_list  *lst;
    char    *tmp;

    tmp = NULL;
    lexer = init_lexer(src);
    token = lexer_get_next_token(lexer);
    lst = NULL;
    while(token)
    {
        lst = add_node_in_lst(token->val, token->type, lst);
        if (token->type == t_herdoc)
        {
            token = lexer_get_next_token(lexer);
            if (!token && token->type != t_args && token->type != t_string)
            {
                lst->val[1] = ft_strdup( token->val);
                free(token->val);
                lst->v_type[1] = t_command;
            }
            token = lexer_get_next_token(lexer);
            if (!token && token->type != t_args && token->type != t_string)
            {
                printf("syntax error near unexpected token \n");
                return lst;
            }
            lst->val[1] = ft_strdup( token->val);
            free(token->val);
            lst->v_type[1] = t_end;
            token = lexer_get_next_token(lexer);
            if (token)
            {
                while (token && (token->type == t_args || token->type == t_string))
                {
                    tmp = ft_strjoin(tmp, token->val);
                    free(token->val);
                    tmp = ft_strjoin(tmp, " ");
                    token = lexer_get_next_token(lexer);
                }
                lst->val[2] = ft_strdup(tmp);
                free(tmp);
                lst->v_type[2] = t_args;
            }
        }
        else if (token->type == t_input || token->type == t_output)
        {
            token = lexer_get_next_token(lexer);
            if (!token && token->type != t_args && token->type != t_string)
            {
                printf("syntax error near unexpected token \n");
                return lst;
            }
            lst->val[1] = token->val;
            free(token->val);
            lst->v_type[1] = t_file;
        }
        else
        {
            token = lexer_get_next_token(lexer);
            if (token)
            {
                while (token && (token->type == t_args || token->type == t_string))
                {
                    tmp = ft_strjoin(tmp, token->val);
                    free(token->val);
                    tmp = ft_strjoin(tmp, " ");
                    token = lexer_get_next_token(lexer);
                }
                lst->val[1] = ft_strdup(tmp);
                free(tmp);
                lst->v_type[1] = t_args;
            }
        }
        token = lexer_get_next_token(lexer);
    }
    return (lst);
}