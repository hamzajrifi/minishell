
#include "header/minishell.h"

void    checksignal(int nbr)
{
    if (nbr == SIGINT)
        exit(1);
}

void    ft_mini(char *src)
{
    t_list *lst;
    int     i;
    lst = ft_parser(src);
    
    i = 0;
    while (lst->v_type[i] != 0 && lst->val[i])
    {
        printf("lst = %s , value = %d\n", lst->val[i], lst->v_type[i]);
        i++;
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