/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <hjrifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:39 by hjrifi            #+#    #+#             */
/*   Updated: 2022/05/30 18:13:29 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include "utiles_functions.h"

//// lexer
typedef struct  lexer_t
{
    char    c;
    unsigned int i;
    char    *src;
} lexer_t;


// token

typedef struct token_struct
{
    enum {
        t_command = 1,
        t_args,
        t_herdoc,
        t_append,
        t_string,
        t_file,
        t_input,
        t_end,
        t_output,
        t_l_parenthesis,
        t_r_parenthesis,
        t_pip,
        t_or,
        t_and,
    } type;

    char *val;
} token_t;

typedef struct t_list
{
    char            **val;
    int             *v_type;
    struct t_list   *next;
}t_list;


void    ft_mini(char *src);
lexer_t *init_lexer(char *src);
void    lexer_advance(lexer_t *lexer);
void    lixer_skip_whitespace(lexer_t *lexer);
token_t *lexer_get_next_token(lexer_t *lexer);
token_t *lexer_collect_string(lexer_t *lexer);
token_t *lexer_collect_arg(lexer_t *lexer);
char	*check_var(lexer_t *lexer);
char    *lexer_get_current_char_as_string(lexer_t *lexer);
token_t *lexer_advance_with_token(lexer_t *lexer, token_t *token);
token_t *init_token(int t_type, char *val);


//// parser

t_list  *ft_parser(char *src);

#endif


/*

char    **val;
int     *n_type;
int     cont;

i = 0;
while (i < cont)
{
    if (n_type[i] == 1) ///// command
    {
        
    }
    else if (n_type[i] == 2 ) //// arg
    {
        val[i] = "-ls";
    }
    else if (n_type[i] == 3 ) //// herdoc
    else if (n_type[i] == 4 ) //// append
    else if (n_type[i] == 5 ) //// string
    else if (n_type[i] == 6 ) //// input 
    
    
    i++;
}
*/