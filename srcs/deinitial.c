#include "so_long.h"

#ifdef CURRENT_OS_LINUX

static void	ft_destroy_mlx(void	*ptr)
{
	mlx_destroy_display(ptr);
	ptr = NULL;
}
#else

static void	ft_destroy_mlx(void	*ptr)
{
	(void)ptr;
}
#endif

static void	ft_deinital_file(t_file	*file)
{
	if (file == NULL || file->lines == NULL)
		return ;
	while (file->count && file->lines[file->count - 1])
	{
		free(file->lines[file->count - 1]);
		--file->count;
	}
	free(file->lines);
	file->lines = NULL;
	file->length = 0;
}

int	ft_deinitial_mlx(t_environment	*env)
{
	if (env == NULL)
		return (EXIT_FAILURE);
	if (env->mlx != NULL && env->game_over_win.ptr != NULL)
	{
		mlx_destroy_window(env->mlx, env->game_over_win.ptr);
		env->game_over_win.ptr = NULL;
	}
	if (env->mlx != NULL && env->main_win.ptr != NULL)
	{
		mlx_destroy_window(env->mlx, env->main_win.ptr);
		env->main_win.ptr = NULL;
	}
	if (env->mlx != NULL)
		ft_destroy_mlx(env->mlx);
	return (EXIT_SUCCESS);
}

void	ft_main_deinitial(t_environment	*env)
{
	if (env == NULL)
		return ;
	ft_deinital_file(&env->file);
	ft_deinitial_array(NULL, &env->paths.character, NULL);
	ft_deinitial_array(NULL, &env->paths.enemy, NULL);
	ft_deinitial_array(NULL, &env->paths.other, NULL);
	ft_deinitial_array(NULL, &env->paths.score, NULL);
	ft_deinitial_array(env->mlx, &env->images.character, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.enemy, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.other, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.score, mlx_destroy_image);
	ft_deinitial_mlx(env);
}
