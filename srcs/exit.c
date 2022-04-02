#include "so_long.h"

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
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
