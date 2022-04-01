#include "so_long.h"

void	ft_game_over(t_environment	*env)
{
	if (env == NULL)
		return ;
	env->game_over_win.ptr = mlx_new_window(env->mlx, 600, 400, "Game over!");
	mlx_put_image_to_window(env->mlx, env->game_over_win.ptr, env->images.game_over, 0, 0);
	mlx_hook(env->game_over_win.ptr, KeyPress | KeyRelease, KeyPressMask | KeyReleaseMask, ft_action_key, env);
}
