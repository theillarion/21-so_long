/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:50 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 15:12:16 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_do_step_on_axis(t_environment	*env,	t_player	*hero,
	void	**images, t_axis old_axis)
{
	int	step_x;
	int	step_y;
	int	current_x;
	int	current_y;

	step_x = (hero->x * env->game.size_pixels - old_axis.x) / env->game
		.size_pixels;
	step_y = (hero->y * env->game.size_pixels - old_axis.y) / env->game
		.size_pixels;
	current_x = old_axis.x;
	current_y = old_axis.y;
	while (current_x != hero->x * env->game.size_pixels
		|| current_y != hero->y * env->game.size_pixels)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			images[hero->current_position], current_x, current_y);
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.other.ptr[ImageIdle], old_axis.x, old_axis.y);
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.other.ptr[ImageIdle], hero->x * env->game.size_pixels,
			hero->y * env->game.size_pixels);
		current_x += step_x;
		current_y += step_y;
	}
}

static void	ft_do_step(t_environment	*env, t_player	*hero,
				void	**images, int	*i)
{
	int	old_x;
	int	old_y;

	old_x = hero->x * env->game.size_pixels;
	old_y = hero->y * env->game.size_pixels;
	if (ft_check_step(env, &hero->x, &hero->y, hero->current_position))
		++*i;
	else
		return ;
	ft_do_step_on_axis(env, hero, images, ft_create_axis(old_x, old_y));
	mlx_put_image_to_window(env->mlx, env->main_win.ptr,
		images[hero->current_position], hero->x * env->game.size_pixels,
		hero->y * env->game.size_pixels);
}

static void	ft_do_actions(t_environment	*env, t_player	*hero,
							void	**images, int	*i)
{
	if (env->game.is_end_game)
		return ;
	if (env != NULL && hero->current_position != hero->next_position)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			images[hero->next_position], hero->x * env->game.size_pixels,
			hero->y * env->game.size_pixels);
		hero->current_position = hero->next_position;
		++*i;
	}
	else if (env != NULL)
		ft_do_step(env, hero, images, i);
	if (env != NULL && ((env->map[ImageCollectible].value == 0
				&& env->map[ImageExit].value == 0) || env->game.is_end_game))
	{
		if (env->game.is_destroy)
			ft_destroy_hero(env);
		env->game.is_action = false;
		ft_game_over(env);
	}
}

static void	ft_do_action_enemy(t_environment	*env)
{
	int			count_do;
	t_ushort	i;

	srand(time(NULL));
	i = 0;
	count_do = 0;
	env->game.is_hero = false;
	while (i < env->map[ImageEnemy].value)
	{
		env->game.enemy[i]->next_position = rand() % 4;
		env->game.hero_number = i;
		ft_do_actions(env, env->game.enemy[i],
			env->images.enemy.ptr, &count_do);
		++i;
	}
}

int	ft_render_next_frame(t_environment	*env)
{
	static int	i = 0;
	static int	tick = 0;
	int			prev_i;

	if (env == NULL || env->game.is_end_game)
		return (EXIT_FAILURE);
	if (env->map[ImageEnemy].value > 0 && tick == 3000)
	{
		ft_do_action_enemy(env);
		tick = 0;
	}
	if (env->game.enemy != NULL)
		++tick;
	if (env->game.is_action == false)
		return (EXIT_SUCCESS);
	prev_i = i;
	env->game.is_hero = true;
	ft_do_actions(env, &env->game.hero, env->images.character.ptr, &i);
	if (prev_i != i)
		ft_render_status_bar(env);
	env->game.is_action = false;
	return (EXIT_SUCCESS);
}
