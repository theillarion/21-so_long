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
		ft_putend_with_color_fd(COLOR_LGREEN, "Start game!", STDOUT_FILENO);
		mlx_hook(env.main_win.ptr, KeyPress,
			KeyPressMask, ft_action_key_press, &env);
		mlx_hook(env.main_win.ptr, KeyRelease,
			KeyReleaseMask, ft_action_key_release, &env);
		mlx_hook(env.main_win.ptr, DestroyNotify,
			ButtonReleaseMask, ft_success, &env);
		mlx_loop_hook(env.mlx, render_next_frame, &env);
		mlx_loop(env.mlx);
		ft_success(&env);
	}
	ft_putendl_fd("Error\nwrong arguments", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
