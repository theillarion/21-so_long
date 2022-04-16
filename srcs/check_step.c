#include "so_long.h"

static void	ft_player_destroyed(t_environment	*env)
{
	env->game.is_end_game = true;
	env->game.is_destroy = true;
}

static bool	ft_is_step_available_for_players(t_environment	*env, int x, int y)
{
	long	i;

	if (!env->game.is_hero && x == env->game.hero.x && y == env->game.hero.y)
	{
		ft_player_destroyed(env);
		return (false);
	}
	else
	{
		i = -1;
		while (++i < env->map[ImageEnemy].value)
		{
			if (x == env->game.enemy[i]->x && y == env->game.enemy[i]->y)
			{
				if (!env->game.is_hero && i == env->game.hero_number)
					continue ;
				if (env->game.is_hero)
					ft_player_destroyed(env);
				return (false);
			}
		}
	}
	return (true);
}

static bool	ft_is_step_available(t_environment	*env, int y, int x)
{
	if (env == NULL)
		return (false);
	if (ft_is_step_available_for_players(env, x, y) == false)
		return (false);
	else if (env->file.lines[y][x] == env->map[ImageIdle].key
		|| env->file.lines[y][x] == env->map[ImageStartPosition].key
		|| env->file.lines[y][x] == env->map[ImageEnemy].key)
		return (true);
	else if (env->file.lines[y][x] == env->map[ImageCollectible].key
		&& env->game.is_hero)
	{
		env->file.lines[y][x] = env->map[ImageIdle].key;
		--env->map[ImageCollectible].value;
		return (true);
	}
	else if (env->map[ImageCollectible].value == 0 && env->game.is_hero
		&& env->file.lines[y][x] == env->map[ImageExit].key)
	{
		env->file.lines[y][x] = env->map[ImageIdle].key;
		--env->map[ImageExit].value;
		return (true);
	}
	return (false);
}

bool	ft_check_step(t_environment	*env, int	*x, int	*y,
			t_ushort	current_position)
{
	if (env == NULL || x == NULL || y == NULL)
		return (false);
	if (current_position == PositionUp
		&& (*y) * env->game.size_pixels - env->game.size_pixels >= 0
		&& ft_is_step_available(env, *y - 1, *x) == true)
		*y -= 1;
	else if (current_position == PositionDown && (*y)
		* env->game.size_pixels + env->game.size_pixels < env->main_win.height
		&& ft_is_step_available(env, *y + 1, *x) == true)
		*y += 1;
	else if (current_position == PositionLeft
		&& (*x) * env->game.size_pixels - env->game.size_pixels >= 0
		&& ft_is_step_available(env, *y, *x - 1) == true)
		*x -= 1;
	else if (current_position == PositionRight && (*x)
		* env->game.size_pixels + env->game.size_pixels < env->main_win.width
		&& ft_is_step_available(env, *y, *x + 1) == true)
		*x += 1;
	else
		return (false);
	return (true);
}
