


#include <fcntl.h>
#include <stdio.h>
#include "shell.h"

int main()
{
    int i = 0;
    int fd[100];
    char *str;

    while (i < 4)
    {
        str = ft_strjoin("/tmp/test", ft_itoa(i));
        fd[i] = open(str, O_CREAT, O_RDWR, O_TRUNC, 0644);
        printf("%d\n", fd[i]);
        i++;
    }
}