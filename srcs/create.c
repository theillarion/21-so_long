#include "so_long.h"

bool	ft_create_mlx(t_environment	*env)
{
	int width;
	int height;

	width = 0;
	height = 0;
	if (env == NULL)
		return (false);
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return (false);
	//mlx_get_screen_size(env->mlx, &width, &height);
	//env->main_win.width = 2500;
	//env->main_win.height = 1400;
	//if (width== 0 || height == 0)
	//	return (false);
	env->main_win.width = 2500;
	env->main_win.height = 1400 * 0.9;
	env->main_win.height -= HeightWordImage;
	return (true);
}
