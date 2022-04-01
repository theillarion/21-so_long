#include "so_long.h"

static void	ft_clean(t_environment	*env)
{
	size_t	i;

	i = 0;
	if (env->file.lines != NULL)
	{
		while (i != env->file.count || env->file.lines[i] != NULL)
		{
			free(env->file.lines[i]);
			++i;
		}
		free(env->file.lines);
		env->file.lines = NULL;
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
	if (env == NULL)
	{
		//...
		exit(EXIT_FAILURE);
	}
	if (env->game_over_win.ptr != NULL)
		mlx_destroy_window(env->mlx, env->game_over_win.ptr);
	if (env->main_win.ptr != NULL)
		mlx_destroy_window(env->mlx, env->main_win.ptr);
	mlx_destroy_display(env->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
