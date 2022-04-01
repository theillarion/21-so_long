#include "so_long.h"

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
		mlx_hook(env.game_w.ptr, KeyPress | KeyRelease,
			KeyPressMask | KeyReleaseMask, ft_close_with_key, &env);
		mlx_hook(env.game_w.ptr, DestroyNotify,
			ButtonReleaseMask, ft_destroy, &env);
		mlx_loop_hook(env.mlx, render_next_frame, &env);
		mlx_loop(env.mlx);
		exit(EXIT_SUCCESS);
	}
	ft_putendl_fd("Error\nwrong arguments", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
