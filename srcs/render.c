#include "so_long.h"

static bool	ft_check(t_environment	*env, int y, int x)
{
	if (env == NULL)
		return (false);
	x /= env->game.size_pixels;
	y /= env->game.size_pixels;
	if (env->file.lines[y][x] == env->map[SymbolIdle].key
		|| env->file.lines[y][x] == env->map[SymbolStartPosition].key)
		return (true);
	else if (env->file.lines[y][x] == env->map[SymbolCollectible].key)
	{
		env->file.lines[y][x] = env->map[SymbolIdle].key;
		--env->map[SymbolCollectible].value;
		return (true);
	}
	else if (env->map[SymbolCollectible].value == 0
		&& env->file.lines[y][x] == env->map[SymbolExit].key)
	{
		env->file.lines[y][x] = env->map[SymbolIdle].key;
		--env->map[SymbolExit].value;
		return (true);
	}
	return (false);
}

/*void	ft_sprite_character(t_environment	*env, int step, bool is_axis_x)
{
	int	x;
	int y;
	int i;

	if (env == NULL)
		return ;
	x = env->game.x * env->game.size_pixels;
	y = env->game.y * env->game.size_pixels;
	if (env->game.size_pixels >= 8)
		i = step / 8;
	else
		i = step / 4;
	if (is_axis_x)
	{
		while (x != env->game.x * env->game.size_pixels + step)
		{
			mlx_put_image_to_window(env->mlx, env->main_win.ptr, env->images.character.ptr[env->game.current_position], x, y);
			mlx_put_image_to_window(env->mlx, env->main_win.ptr, env->images.other.ptr[SymbolIdle], x, y);
			x += i;
		}
		mlx_put_image_to_window(env->mlx, env->main_win.ptr, env->images.character.ptr[env->game.current_position], x, y);
	}
	else
	{
		while (y != env->game.y * env->game.size_pixels + step)
		{
			mlx_put_image_to_window(env->mlx, env->main_win.ptr, env->images.character.ptr[env->game.current_position], x, y);
			mlx_put_image_to_window(env->mlx, env->main_win.ptr, env->images.other.ptr[SymbolIdle], x, y);
			y += i;
		}
		mlx_put_image_to_window(env->mlx, env->main_win.ptr, env->images.character.ptr[env->game.current_position], x, y);
	}
}
*/

static bool	fd_do_step(t_environment	*env, int	*x, int	*y)
{
	if (env == NULL)
		return (false);
	if (env->game.current_position == PositionUp
		&& *y - env->game.size_pixels >= 0
		&& ft_check(env, *y - env->game.size_pixels, *x) == true)
		*y -= env->game.size_pixels;
	else if (env->game.current_position == PositionDown
		&& *y + env->game.size_pixels < env->main_win.height
		&& ft_check(env, *y + env->game.size_pixels, *x) == true)
		*y += env->game.size_pixels;
	else if (env->game.current_position == PositionLeft
		&& *x - env->game.size_pixels >= 0
		&& ft_check(env, *y, *x - env->game.size_pixels) == true)
		*x -= env->game.size_pixels;
	else if (env->game.current_position == PositionRight
		&& *x + env->game.size_pixels < env->main_win.width
		&& ft_check(env, *y, *x + env->game.size_pixels) == true)
		*x += env->game.size_pixels;
	else
		return (false);
	return (true);
}

static void	ft_do_action(t_environment	*env, int x, int y, int	*i)
{
	if (env != NULL && env->game.current_position != env->game.next_position)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.character.ptr[env->game.next_position], x, y);
		env->game.current_position = env->game.next_position;
		++*i;
	}
	else if (env != NULL)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.other.ptr[SymbolIdle], x, y);
		if (fd_do_step(env, &x, &y) == true)
			++*i;
		env->game.x = x / env->game.size_pixels;
		env->game.y = y / env->game.size_pixels;
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.character.ptr[env->game.current_position], x, y);
	}
	if (env != NULL && env->map[SymbolCollectible].value == 0
		&& env->map[SymbolExit].value == 0)
	{
		env->game.is_action = false;
		ft_game_over(env);
	}
}

int	render_next_frame(t_environment	*env)
{
	static int	i;
	int			prev_i;
	int			x;
	int			y;

	if (env == NULL || env->game.is_action == false || env->game.is_end_game)
		return (EXIT_FAILURE);
	x = env->game.x * env->game.size_pixels;
	y = env->game.y * env->game.size_pixels;
	prev_i = i;
	ft_do_action(env, x, y, &i);
	if (prev_i != i)
		ft_render_status_bar(env);
	env->game.is_action = false;
	return (EXIT_SUCCESS);
}
