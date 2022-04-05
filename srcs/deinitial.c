#include "so_long.h"

static void	ft_deinital_file(t_file	*file)
{
	size_t	i;

	if (file == NULL || file->lines == NULL)
		return ;
	i = 0;
	while (file->lines[i])
	{
		free(file->lines[i]);
		++i;
	}
	free(file->lines);
	file->lines = NULL;
}

static void	ft_deinital_paths(t_paths	*paths)
{
	if (paths == NULL)
		return ;
	ft_deinitial_array(&paths->path_to_character);
	ft_deinitial_array(&paths->path_to_other);
	ft_smart_free(&paths->path_to_game_over);
}

static void	ft_deinitial_images(t_environment	*env)
{
	t_ushort	i;

	if (env == NULL || env->mlx == NULL)
		return ;
	i = 0;
	while (i < env->images.character.count)
		mlx_destroy_image(env->mlx, env->images.character.ptr[i++]);
	free(env->images.character.ptr);
	env->images.character.ptr = NULL;
	i = 0;
	while (i < env->images.other.count)
		mlx_destroy_image(env->mlx, env->images.other.ptr[i++]);
	free(env->images.other.ptr);
	env->images.other.ptr = NULL;
	mlx_destroy_image(env->mlx, env->images.game_over);
	env->images.game_over = NULL;
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
	{
		//mlx_destroy_display(env->mlx);
		free(env->mlx);
		env->mlx = NULL;
	}
	return (EXIT_SUCCESS);
}

void	ft_main_deinitial(t_environment	*env)
{
	if (env == NULL)
		return ;
	ft_deinital_file(&env->file);
	ft_deinital_paths(&env->paths);
	ft_deinitial_images(env);
	ft_deinitial_mlx(env);
}
