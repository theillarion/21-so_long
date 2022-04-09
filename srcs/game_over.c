#include "so_long.h"

/*int	ft_close_game_over_window(t_environment	*env)
{
	if (env == NULL)
		return (-1);
	if (env->mlx != NULL && env->game_over_win.ptr != NULL)
	{
		mlx_destroy_image(env->mlx, env->images.game_over);
		mlx_clear_window(env->mlx, env->game_over_win.ptr);
		mlx_destroy_window(env->mlx, env->game_over_win.ptr);
		env->game_over_win.ptr = NULL;
	}
	return (0);
}
*/
void	ft_game_over(t_environment	*env)
{
	if (env == NULL)
		return ;
	env->game.is_end_game = true;
	env->game_over_win.ptr = mlx_new_window(env->mlx, 600, 400, "Game over!");
	mlx_put_image_to_window(env->mlx, env->game_over_win.ptr,
		env->images.score.ptr[ImageGameOver], 0, 0);
	mlx_hook(env->game_over_win.ptr, KeyRelease,
		KeyReleaseMask, ft_action_key_release, env);
	mlx_hook(env->game_over_win.ptr, DestroyNotify,
		ButtonReleaseMask, ft_success, env);
}
