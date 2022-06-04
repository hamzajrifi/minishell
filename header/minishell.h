/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:39 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/04 15:14:35 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include "utiles_functions.h"
#include "../shell.h"

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
        t_args = 2,
        t_herdoc = 3,
        t_append = 4,
        t_file = 5,
        t_output = 8,
        t_end = 7,
        t_input = 6,
        t_l_parenthesis = 9,
        t_r_parenthesis = 10,
        t_pip = 11,
        t_or = 12,
        t_and = 13,
        t_error = 14,
    } type;

    char *val;
} token_t;



void    ft_mini(t_shell *mini, char *src);
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

