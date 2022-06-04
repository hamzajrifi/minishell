#include "../shell.h"

void	ft_pwd(int fd)
{
	char	buff[256];

	ft_putendl_fd(getcwd(buff, sizeof(buff)), fd);
}
