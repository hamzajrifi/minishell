
#include "header/minishell.h"

void    checksignal(int nbr)
{
    if (nbr == SIGINT)
        exit(1);
}

void    ft_mini(char *src)
{
    lexer_t *lexer;
    token_t *token;

    lexer = init_lexer(src);
    // printf("src = %s\n", src);
    token = NULL;
    while((token = lexer_get_next_token(lexer)))
    {
        printf("Token(%d, %s)\n", token->type, token->val);
    }

}

int main(void)
{
    char    *src;

	signal(SIGINT, checksignal);
    while(1337)
    {
        src = readline("mimishell :>");
        ft_mini(src);
		add_history(src);
        free(src);
    }
    return (0);
}