/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinitial.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:06 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:52:06 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	ft_deinitial_game(t_game	*game, t_ushort count_enemy)
{
	t_ushort	i;

	if (game == NULL || game->enemy == NULL)
		return ;
	i = 0;
	while (i < count_enemy)
	{
		free(game->enemy[i]);
		++i;
	}
	free(game->enemy);
	game->enemy = NULL;
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
		ft_destroy_display(&env->mlx);
	return (EXIT_SUCCESS);
}

void	ft_main_deinitial(t_environment	*env)
{
	if (env == NULL)
		return ;
	ft_deinital_file(&env->file);
	ft_deinitial_game(&env->game, (t_ushort)env->map[ImageEnemy].value);
	ft_deinitial_array(NULL, &env->paths.character, NULL);
	ft_deinitial_array(NULL, &env->paths.enemy, NULL);
	ft_deinitial_array(NULL, &env->paths.other, NULL);
	ft_deinitial_array(NULL, &env->paths.score, NULL);
	ft_deinitial_array(NULL, &env->paths.destroy, NULL);
	ft_deinitial_array(env->mlx, &env->images.character, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.enemy, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.other, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.score, mlx_destroy_image);
	ft_deinitial_array(env->mlx, &env->images.destroy, mlx_destroy_image);
	ft_deinitial_mlx(env);
}
