#include "so_long.h"

static void	ft_clean(t_environment	*env)
{
	size_t	i;

	i = 0;
	if (env->file.lines != NULL)
	{
		while (i != env->file.count || env->file.lines[i] != NULL)
		{
			ft_smart_free((void *)&env->file.lines[i]);
			++i;
		}
		ft_smart_free((void *)&env->file.lines);
	}
}

void	ft_fail(t_environment	*env, const char	*msg_err, bool is_errno)
{
	ft_clean(env);
	if (is_errno && errno != 0)
		perror(msg_err);
	else
		ft_putendl_fd((char *)msg_err, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_success(t_environment	*env, const char	*msg)
{
	ft_clean(env);
	ft_putendl_fd((char *)msg, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

int	ft_destroy(t_environment	*env)
{
	mlx_destroy_window(env->mlx, env->game_w.ptr);
	mlx_destroy_display(env->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
