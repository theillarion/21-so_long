#include "so_long.h"
#include <stdio.h>

void	ft_fail(t_environment	*env, const char	*msg_err, bool is_errno)
{
	ft_main_deinitial(env);
	if (is_errno == true && errno != 0)
		perror(msg_err);
	else
		ft_putendl_fd((char *)msg_err, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	ft_success(t_environment	*env)
{
	ft_main_deinitial(env);
	ft_putend_with_color_fd(COLOR_LGREEN, "Game over!", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	ft_exit_fail(const char	*msg_err)
{
	ft_putendl_fd(msg_err, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_mlx_no_destroy(void	*ptr)
{
	(void)ptr;
}