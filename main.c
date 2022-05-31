
#include "header/minishell.h"

void    checksignal(int nbr)
{
    if (nbr == SIGINT)
        exit(1);
}

void    ft_mini(char *src)
{
    // t_list *lst;
    
    // lst =
     ft_parser(src);

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