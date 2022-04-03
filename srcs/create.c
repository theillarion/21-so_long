#include "so_long.h"

bool	ft_create_mlx(t_environment	*env)
{
	if (env == NULL)
		return (false);
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return (false);
	mlx_get_screen_size(env->mlx, (int *)&env->main_win.width,
		(int *)&env->main_win.height);
	if (env->main_win.width == 0 || env->main_win.height == 0)
		return (false);
	env->main_win.height *= 0.9;
	return (true);
}
