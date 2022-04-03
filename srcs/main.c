#include "so_long.h"

void	*ft_check(const void	*ptr)
{
	if (ptr != NULL)
		return ((void *)ptr);
	exit(EXIT_FAILURE);
	return (NULL);	
}

int	main(int argc, char	**argv)
{
	t_environment	env;

	if (argc == 2)
	{
		errno = 0;
		if (ft_main_initial(&env) == false)
			ft_fail(&env, "Error\ninitial", false);
		if (ft_get_file(&env.file, argv[1]) == false)
			ft_fail(&env, "Error\n", true);
		if (ft_validation(&env) == false)
			ft_fail(&env, "Error\nwrong map", false);
		if (ft_main_fill(&env) == false)
			ft_fail(&env, "Error\nfill", false);
		mlx_hook(env.main_win.ptr, KeyPress | KeyRelease,
			KeyPressMask | KeyReleaseMask, ft_action_key, &env);
		mlx_hook(env.main_win.ptr, DestroyNotify,
			ButtonReleaseMask, ft_success, &env);
		mlx_loop_hook(env.mlx, render_next_frame, &env);
		mlx_loop(ft_check(env.mlx));
		ft_success(&env);
	}
	ft_putendl_fd("Error\nwrong arguments", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
