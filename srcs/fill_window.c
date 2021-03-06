/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:21 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:52:22 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	ft_handler_map_enemy(t_environment	*env, const char symbol,
	const t_ushort x, const t_ushort y)
{
	static t_ushort	i;

	if (env->game.enemy != NULL && symbol == env->map[ImageEnemy].key)
	{
		if (i >= env->map[ImageEnemy].value)
			return (false);
		mlx_put_image_to_window(env->mlx,
			env->main_win.ptr, env->images.enemy.ptr[PositionUp],
			x * env->game.size_pixels, y * env->game.size_pixels);
		env->game.enemy[i]->x = x;
		env->game.enemy[i]->y = y;
		++i;
		return (true);
	}
	return (false);
}

static bool	ft_handler_map(t_environment	*env, const char symbol,
	const t_ushort x, const t_ushort y)
{
	if (symbol == env->map[ImageIdle].key
		|| symbol == env->map[ImageWall].key
		|| symbol == env->map[ImageCollectible].key
		|| symbol == env->map[ImageExit].key)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.other.ptr[ft_symbol_to_int(env->map, symbol)],
			x * env->game.size_pixels, y * env->game.size_pixels);
		return (true);
	}
	else if (symbol == env->map[ImageStartPosition].key)
	{
		mlx_put_image_to_window(env->mlx,
			env->main_win.ptr, env->images.character.ptr[PositionUp],
			x * env->game.size_pixels, y * env->game.size_pixels);
		env->game.hero.x = x;
		env->game.hero.y = y;
		return (true);
	}
	return (false);
}

bool	ft_fill_window(t_environment	*env)
{
	t_ushort	i;
	t_ushort	j;

	if (env == NULL)
		return (false);
	i = 0;
	while (i < env->file.count)
	{
		j = 0;
		while (j < env->file.length)
		{
			if (!ft_handler_map(env, env->file.lines[i][j], j, i)
				&& !ft_handler_map_enemy(env, env->file.lines[i][j], j, i))
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

void	ft_fill_status_bar(t_environment	*env)
{
	t_ushort	x;
	t_ushort	y;

	if (env == NULL)
		return ;
	x = env->main_win.status_bar.start_x;
	y = env->main_win.status_bar.start_y;
	if (x != 0)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.score.ptr[ImageScoreWord], 0, y);
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.score.ptr[ImageScoreIdle], WidthImageWord, y);
	}
	mlx_put_image_to_window(env->mlx, env->main_win.ptr,
		env->images.score.ptr[ImageScore0], x, y);
	x += WidthImageNumber;
	while (x < env->main_win.common_width)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.score.ptr[ImageScoreIdle], x, y);
		x += WidthImageNumber;
	}
}

void	ft_set_size_window(t_environment	*env)
{
	env->main_win.width = env->game.size_pixels * env->file.length;
	env->main_win.height = env->game.size_pixels * env->file.count;
	env->main_win.status_bar.start_x = 0;
	env->main_win.status_bar.start_y = env->main_win.height;
	env->main_win.status_bar.width = env->main_win.width;
	env->main_win.status_bar.height = HeightImageWord;
	env->main_win.common_width = env->main_win.width;
	env->main_win.common_height = env->main_win.height
		+ env->main_win.status_bar.height;
}
