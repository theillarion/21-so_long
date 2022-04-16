#include "so_long.h"

#ifdef CURRENT_OS_LINUX

void	ft_destroy_display(void	**ptr)
{
	mlx_destroy_display(*ptr);
	*ptr = NULL;
}
#else

void	ft_destroy_display(void	**ptr)
{
	(void)ptr;
}
#endif

void	ft_destroy_hero(t_environment	*env)
{
	t_ushort	i;

	if (env == NULL)
		return ;
	i = ImageDestroy0;
	while (i <= ImageDestroy8)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.destroy.ptr[i], env->game.hero.x
			* env->game.size_pixels, env->game.hero.y * env->game.size_pixels);
		mlx_do_sync(env->mlx);
		usleep(100000);
		++i;
	}
	mlx_put_image_to_window(env->mlx, env->main_win.ptr,
		env->images.other.ptr[ImageIdle], env->game.hero.x
		* env->game.size_pixels, env->game.hero.y * env->game.size_pixels);
}
