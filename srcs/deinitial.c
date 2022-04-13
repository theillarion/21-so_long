#include "so_long.h"

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

static void	ft_deinital_paths(t_paths	*paths)
{
	if (paths == NULL)
		return ;
	ft_deinitial_array(NULL, &paths->path_to_character, NULL);
	ft_deinitial_array(NULL, &paths->path_to_other, NULL);
	ft_deinitial_array(NULL, &paths->score, NULL);
}

static void	ft_deinitial_images(t_environment	*env)
{
	if (env == NULL || env->mlx == NULL)
		return ;
	ft_deinitial_array(env->mlx, &env->images.character, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.other, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.score, mlx_destroy_image);
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
