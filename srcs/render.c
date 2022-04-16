#include "so_long.h"

static bool	ft_check_hero(t_environment	*env, int x, int y)
{
	long	i;

	if (!env->game.is_hero && x == env->game.hero.x && y == env->game.hero.y)
	{
		env->game.is_end_game = true;
		env->game.is_destroy = true;
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
				{
					env->game.is_destroy = true;
					env->game.is_end_game = true;
				}
				return (false);
			}
		}
	}
	return (true);
}

static bool	ft_check(t_environment	*env, int y, int x)
{
	if (env == NULL)
		return (false);
	if (ft_check_hero(env, x, y) == false)
		return (false);
	else if (env->file.lines[y][x] == env->map[ImageIdle].key
		|| env->file.lines[y][x] == env->map[ImageStartPosition].key
		|| env->file.lines[y][x] == env->map[ImageEnemy].key)
		return (true);
	else if (env->file.lines[y][x] == env->map[ImageCollectible].key)
	{
		env->file.lines[y][x] = env->map[ImageIdle].key;
		--env->map[ImageCollectible].value;
		return (true);
	}
	else if (env->map[ImageCollectible].value == 0
		&& env->file.lines[y][x] == env->map[ImageExit].key)
	{
		env->file.lines[y][x] = env->map[ImageIdle].key;
		--env->map[ImageExit].value;
		return (true);
	}
	return (false);
}

static bool	fd_do_step(t_environment	*env, int	*x, int	*y,
	t_ushort	current_position)
{
	if (env == NULL || x == NULL || y == NULL)
		return (false);
	if (current_position == PositionUp
		&& (*y) * env->game.size_pixels - env->game.size_pixels >= 0
		&& ft_check(env, *y - 1, *x) == true)
		*y -= 1;
	else if (current_position == PositionDown
		&& (*y) * env->game.size_pixels + env->game.size_pixels < env->main_win.height
		&& ft_check(env, *y + 1, *x) == true)
		*y += 1;
	else if (current_position == PositionLeft
		&& (*x) * env->game.size_pixels - env->game.size_pixels >= 0
		&& ft_check(env, *y, *x - 1) == true)
		*x -= 1;
	else if (current_position == PositionRight
		&& (*x) * env->game.size_pixels + env->game.size_pixels < env->main_win.width
		&& ft_check(env, *y, *x + 1) == true)
		*x += 1;
	else
		return (false);
	return (true);
}

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
		env->images.other.ptr[ImageIdle],env->game.hero.x
		* env->game.size_pixels, env->game.hero.y * env->game.size_pixels);
}

static void	ft_do_action(t_environment	*env, t_player	*hero, void	**image, int	*i)
{
	if (env != NULL && hero->current_position != hero->next_position)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			image[hero->next_position],hero->x * env->game.size_pixels,
			hero->y * env->game.size_pixels);
		hero->current_position = hero->next_position;
		++*i;
	}
	else if (env != NULL)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.other.ptr[ImageIdle],hero->x * env->game.size_pixels,
			hero->y * env->game.size_pixels);
		if (fd_do_step(env, &hero->x, &hero->y, hero->current_position) == true)
			++*i;
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			image[hero->current_position], hero->x * env->game.size_pixels,
			hero->y * env->game.size_pixels);
	}
	if (env != NULL && ((env->map[ImageCollectible].value == 0
		&& env->map[ImageExit].value == 0) || env->game.is_end_game))
	{
		if (env->game.is_destroy)
			ft_destroy_hero(env);
		env->game.is_action = false;
		ft_game_over(env);
	}
}

void	ft_do_action_enemy(t_environment	*env)
{
	int	count_do;
	t_ushort	i;

	srand(time(NULL));
	i = 0;
	count_do = 0;
	env->game.is_hero = false;
	while (i < env->map[ImageEnemy].value)
	{
		env->game.enemy[i]->next_position = rand() % 4;
		env->game.hero_number = i;
		ft_do_action(env, env->game.enemy[i], env->images.enemy.ptr, &count_do);
		++i;
	}
}

int	render_next_frame(t_environment	*env)
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
	ft_do_action(env, &env->game.hero, env->images.character.ptr, &i);
	if (prev_i != i)
		ft_render_status_bar(env);
	env->game.is_action = false;
	return (EXIT_SUCCESS);
}
