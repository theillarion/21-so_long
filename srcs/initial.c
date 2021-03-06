/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:38 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:53:54 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_initial_pair(t_pair	*map)
{
	t_ushort	i;

	if (map == NULL)
		return ;
	map[ImageIdle].key = '0';
	map[ImageWall].key = '1';
	map[ImageCollectible].key = 'C';
	map[ImageExit].key = 'E';
	map[ImageEnemy].key = 'F';
	map[ImageStartPosition].key = 'P';
	i = 0;
	while (i != COUNT_PAIRS)
		map[i++].value = 0;
}

static void	ft_initial_file(t_file	*file)
{
	if (file == NULL)
		return ;
	file->count = 0;
	file->length = 0;
	file->lines = NULL;
}

static void	ft_initial_window(t_window	*window, bool is_used_status_bar)
{
	if (window == NULL)
		return ;
	window->ptr = NULL;
	window->start_x = 0;
	window->start_y = 0;
	window->width = 0;
	window->height = 0;
	window->common_width = 0;
	window->common_height = 0;
	window->is_used_status_bar = is_used_status_bar;
	if (is_used_status_bar)
	{
		window->status_bar.start_x = 0;
		window->status_bar.start_y = 0;
		window->status_bar.width = 0;
		window->status_bar.height = 0;
	}
}

static void	ft_initial_game(t_game	*game)
{
	if (game == NULL)
		return ;
	game->size_pixels = 0;
	game->hero_number = 0;
	game->is_hero = true;
	game->is_action = false;
	game->is_end_game = false;
	game->is_destroy = false;
	game->hero.x = 0;
	game->hero.y = 0;
	game->hero.current_position = PositionUp;
	game->hero.next_position = PositionUp;
	game->enemy = NULL;
}

bool	ft_main_initial(t_environment	*env)
{
	if (env == NULL)
		return (false);
	env->mlx = NULL;
	ft_initial_file(&env->file);
	ft_initial_pair(env->map);
	ft_initial_array(&env->paths.character);
	ft_initial_array(&env->paths.enemy);
	ft_initial_array(&env->paths.other);
	ft_initial_array(&env->paths.score);
	ft_initial_array(&env->paths.destroy);
	ft_initial_array(&env->images.character);
	ft_initial_array(&env->images.enemy);
	ft_initial_array(&env->images.other);
	ft_initial_array(&env->images.score);
	ft_initial_array(&env->images.destroy);
	ft_initial_window(&env->main_win, true);
	ft_initial_window(&env->game_over_win, false);
	ft_initial_game(&env->game);
	return (true);
}
