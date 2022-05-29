
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
    while((lexer->c >= '0' && lexer->c <= '9') || (lexer->c >= 'a' && lexer->c <= 'z') || (lexer->c >= 'A' && lexer->c <= 'Z'))
            return (lexer_collect_id(lexer));
        if (lexer->c == '"')
            return (lexer_collect_string(lexer));
        if (lexer->c == '|')
            return (lexer_advance_with_token(lexer , init_token(t_pip, lexer_get_current_char_as_string(lexer))));
        if (lexer->c == '=')
            return (lexer_advance_with_token(lexer , init_token(t_equal, lexer_get_current_char_as_string(lexer)))); 
        if (lexer->c == '$')
            return (lexer_advance_with_token(lexer , init_token(t_dollar, lexer_get_current_char_as_string(lexer))));
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

token_t *lexer_collect_string(lexer_t *lexer)
{
    char    *tmp;
    char    *str;
    int     i;

    i = 0;
    lexer_advance(lexer);
    while(lexer->c != '"')
    {
        tmp = lexer_get_current_char_as_string(lexer); // sheck sigfault..
        str = ft_strjoin(str, tmp);
        free(tmp);
        lexer_advance(lexer); 
        i++;        
    }
    lexer_advance(lexer);
    return (init_token(t_string, str));
}

token_t *lexer_collect_id(lexer_t *lexer)
{
    char    *tmp;
    char    *str;

    str = NULL;
    while((lexer->c >= '0' && lexer->c <= '9') || (lexer->c >= 'a' && lexer->c <= 'z') || (lexer->c >= 'A' && lexer->c <= 'Z'))
    {
        tmp = lexer_get_current_char_as_string(lexer); // sheck sigfault..
        str = ft_strjoin(str, tmp);
        free(tmp);
        lexer_advance(lexer);
    }
    return (init_token(t_command, str));
}

char *lexer_get_current_char_as_string(lexer_t *lexer)
{
    char    *str;
    
    str = malloc(sizeof(char) * 2);
    str[0] = lexer->c;
    str[1] = '\0'; 
    return (str);
}