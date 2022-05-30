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
        t_string,
        t_input,
        t_output,
        t_var,
        t_l_parenthesis,
        t_r_parenthesis,
        t_pip,
        t_equal,
        t_number,
        t_or,
        t_and,
    } type;

    char *val;
} token_t;

void    ft_mini(char *src);
lexer_t *init_lexer(char *src);

void    lexer_advance(lexer_t *lexer);

void    lixer_skip_whitespace(lexer_t *lexer);

token_t *lexer_get_next_token(lexer_t *lexer);

token_t *lexer_collect_string(lexer_t *lexer);
token_t *lexer_collect_arg(lexer_t *lexer);
char	*check_var(lexer_t *lexer);

char *lexer_get_current_char_as_string(lexer_t *lexer);
token_t *lexer_advance_with_token(lexer_t *lexer, token_t *token);
token_t *init_token(int t_type, char *val);
#endif