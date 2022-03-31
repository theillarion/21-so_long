#include "so_long.h"

int ft_destroy(t_environment	*env)
{
	mlx_destroy_window(env->mlx, env->game_w.ptr);
	mlx_destroy_display(env->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int ft_close_with_key(int keycode, t_environment	*env)
{
	ft_putstr_fd("Press KEY: ", STDOUT_FILENO);
	ft_putnbr_fd(keycode, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (keycode == ESC)
		ft_destroy(env);
	else if (keycode >= LEFT && keycode <= DOWN)
	{
		env->game_w.is_action = true;
		env->game_w.next_position = keycode - LEFT;
	}
	return (0);
}

bool	ft_check(t_environment	*env, int y, int	x)
{
	x /= env->game_w.size_pixels;
	y /= env->game_w.size_pixels;
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

void	fd_to_do(t_environment	*env, int	*x, int	*y)
{
	
	if (env->game_w.current_position == PositionUp
		&& *y - env->game_w.size_pixels >= 0
		&& ft_check(env, *y - env->game_w.size_pixels, *x) == true)
		*y -= env->game_w.size_pixels;
	else if (env->game_w.current_position == PositionDown
		&& *y + env->game_w.size_pixels < env->game_w.height
		&& ft_check(env, *y + env->game_w.size_pixels, *x) == true)
		*y += env->game_w.size_pixels;
	else if (env->game_w.current_position == PositionLeft
		&& *x - env->game_w.size_pixels >= 0
		&& ft_check(env, *y, *x - env->game_w.size_pixels) == true)
		*x -= env->game_w.size_pixels;
	else if (env->game_w.current_position == PositionRight
		&& *x + env->game_w.size_pixels < env->game_w.width
		&& ft_check(env, *y, *x + env->game_w.size_pixels) == true)
		*x += env->game_w.size_pixels;
}

int	render_next_frame(t_environment	*env)
{
	int	x;
	int	y;

	if (env != NULL && env->game_w.is_action)
	{
		mlx_do_sync(env->mlx);
		x = env->game_w.x * env->game_w.size_pixels;
		y = env->game_w.y * env->game_w.size_pixels;
		if (env->game_w.current_position != env->game_w.next_position)
		{
			mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.character.ptr[env->game_w.next_position], x, y);
			env->game_w.current_position = env->game_w.next_position;
		}
		else
		{
			mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.other.ptr[SymbolIdle], x, y);
			fd_to_do(env, &x, &y);
			env->game_w.x = x / env->game_w.size_pixels;
			env->game_w.y = y / env->game_w.size_pixels;
			mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.character.ptr[env->game_w.current_position], x, y);
		}
		if (env->map[SymbolCollectible].value == 0 && env->map[SymbolExit].value == 0)
		{
			ft_destroy(env);
		}
		env->game_w.is_action = false;
	}
	return (0);
}

int	main(int argc, char	**argv)
{
	t_environment	env;

	if (argc == 2)
	{
		if (ft_main_initial(&env) == false)
			ft_fail(&env, "Error\n", false);
		errno = 0;
		if (ft_get_file(&env.file, argv[1]) == false)
			ft_fail(&env, "Error\nprogram", true);
		else
		{
			if (ft_validation(&env) == false)
				ft_fail(&env, "Error\ninvalid arguments", false);
			else
			{
				if (ft_main_fill(&env) == false)
					ft_fail(&env, "Error\nGGGG", false);
				
				mlx_hook(env.game_w.ptr, KeyPress | KeyRelease, KeyPressMask | KeyReleaseMask, ft_close_with_key, &env);
				mlx_hook(env.game_w.ptr, DestroyNotify, ButtonReleaseMask, ft_destroy, &env);

				mlx_loop_hook(env.mlx, render_next_frame, &env);
				mlx_loop(env.mlx);
			}
				//ft_success(&env, "Success!");
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putendl_fd("Error", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}
