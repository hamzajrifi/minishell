


#include <fcntl.h>
#include <stdio.h>
#include "shell.h"

int main()
{
    int fd = open("test", O_CREAT | O_RDWR  , 0644);
    unlink("test");
}