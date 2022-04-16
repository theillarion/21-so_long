#include "so_long.h"

static void	ft_do_step(t_environment	*env, t_player	*hero,
				void	**images, int	*i)
{
	int	old_x;
	int	old_y;
	int	step_x;
	int	step_y;

	old_x = hero->x * env->game.size_pixels;
	old_y = hero->y * env->game.size_pixels;
	if (ft_check_step(env, &hero->x, &hero->y, hero->current_position))
		++*i;
	else
		return ;
	step_x = (hero->x * env->game.size_pixels - old_x) / env->game.size_pixels;
	step_y = (hero->y * env->game.size_pixels - old_y) / env->game.size_pixels;
	while (old_x != hero->x * env->game.size_pixels
		|| old_y != hero->y * env->game.size_pixels)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.other.ptr[ImageIdle], old_x, old_y);
		old_x += step_x;
		old_y += step_y;
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			images[hero->current_position], old_x, old_y);
		mlx_do_sync(env->mlx);
		usleep(4000);
	}
}

static void	ft_do_actions(t_environment	*env, t_player	*hero,
							void	**images, int	*i)
{
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
	static int	i;
	static int	tick;
	int			prev_i;

	if (env == NULL || env->game.is_end_game)
		return (EXIT_FAILURE);
	if (env->map[ImageEnemy].value > 0 && tick == 10000)
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
