#include "so_long.h"

void	ft_putend_with_color_fd(const char	*color, const char	*message,
	int fd)
{
	if (fd <= 0 || color == NULL || message == NULL)
		return ;
	ft_putstr_fd((char *)color, STDOUT_FILENO);
	ft_putstr_fd((char *)message, STDOUT_FILENO);
	ft_putendl_fd(NOCOLOR, STDOUT_FILENO);
}
