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
    if (v_type == t_args) 
    {
        v_type = 1;
    }    
	new = malloc(sizeof(t_list));
    new->val = malloc (sizeof(char*) * 2);
    new->v_type = malloc(sizeof(int) * 2);
	new->val[0] = str;
    new->val[1] = NULL;
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

t_list  *ft_check_parser(token_t **token, lexer_t *lexer, t_list *lst)
{
    int     i;

    i = 1;
    *token = lexer_get_next_token(lexer);
    while (*token && (*token)->type == t_args)
    {
        
        lst->val =  ft_realloc_char(lst->val); /// return str 
        lst->v_type =  ft_realloc_int(lst->v_type, lst->val); /// return str 
        lst->val[i] = ft_strdup((*token)->val);
        lst->v_type[i++] = (*token)->type;
        *token = lexer_get_next_token(lexer);
    }
    if (i > 1 && lst->v_type[0] == 3)
        lst->v_type[1] = t_end;
    else if (i > 1 && lst->v_type[0] == t_output)
        lst->v_type[1] = t_file;
    if ((*token) && (*token)->type == t_error)
        return (print_error("minishell: syntax error 2"));
    return (lst);
}

t_list    *print_error(char *str)
{
    printf("%s\n",str);
    return (NULL);
}

t_list  *ft_parser(char *src)
{
    lexer_t *lexer;
    token_t *token;
    t_list  *lst;
    t_list  *head;
    
    lexer = init_lexer(src);
    token = lexer_get_next_token(lexer);
    lst = NULL;
    if (token)
        lst = add_node_in_lst(token->val, token->type, lst);
    if(token && token->type == t_error)
        return (print_error("minishell: syntax error 3"));
    head = lst;
    while(token && token->type != t_error)
    {
        if (!(lst = ft_check_parser(&token, lexer, lst)))
			return (NULL);
        if (token && lst)
        {
            if (!(lst = add_node_in_lst(token->val, token->type, head)))
				return(NULL);
            if (token->type > t_output && token->type <= t_error )
            {
                token = lexer_get_next_token(lexer);
                if (!(lst = add_node_in_lst(token->val, token->type, head)))
					return(NULL);
            }
            while (lst->next)
                lst = lst->next;
        }
    }
    return (head);
}