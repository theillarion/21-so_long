#include "so_long.h"

bool	ft_fill_paths(t_paths	*paths, t_ushort	size_pixels)
{
	char	*main_dir;

	if (paths == NULL || size_pixels == 0)
		return (false);
	main_dir = ft_get_main_directory(size_pixels);
	ft_push_move(&paths->path_to_other, ft_strjoin(main_dir, "idle/idle.xpm"));
	ft_push_move(&paths->path_to_other, ft_strjoin(main_dir, "wall/wall.xpm"));
	ft_push_move(&paths->path_to_other,
		(void *)ft_strjoin(main_dir, "collectible/collectible.xpm"));
	ft_push_move(&paths->path_to_other, ft_strjoin(main_dir, "exit/exit.xpm"));
	ft_push_move(&paths->path_to_character, ft_strjoin(main_dir,
			"character/character_left.xpm"));
	ft_push_move(&paths->path_to_character, ft_strjoin(main_dir,
			"character/character_up.xpm"));
	ft_push_move(&paths->path_to_character, ft_strjoin(main_dir,
			"character/character_right.xpm"));
	ft_push_move(&paths->path_to_character, ft_strjoin(main_dir,
			"character/character_down.xpm"));
	paths->path_to_game_over = ft_strdup("images/game_over_600_x_400.xpm");
	if (main_dir != NULL)
		ft_smart_free((void *)&main_dir);
	return (true);
}

bool	ft_fill_images(t_environment	*env, int *x, int *y)
{
	t_ushort	i;

	if (env == NULL || env->mlx == NULL)
		return (false);
	i = 0;
	while (i < env->paths.path_to_other.count)
	{
		ft_push_move(&env->images.other, mlx_xpm_file_to_image(env->mlx,
				env->paths.path_to_other.ptr[i], x, y));
		if (env->images.other.ptr[i++] == NULL || env->images.other.ptr == NULL
			|| *x != env->game.size_pixels || *y != env->game.size_pixels)
			return (false);
	}
	i = 0;
	while (i < env->paths.path_to_character.count)
	{
		ft_push_move(&env->images.character, mlx_xpm_file_to_image(env->mlx,
				env->paths.path_to_character.ptr[i], x, y));
		if (!env->images.character.ptr[i++] || !env->images.character.ptr
			|| *x != env->game.size_pixels || *y != env->game.size_pixels)
			return (false);
	}
	env->images.game_over = mlx_xpm_file_to_image(env->mlx,
			env->paths.path_to_game_over, x, y);
	return (true);
}

static bool	ft_handler_symbols(t_environment	*env, const char symbol,
		const t_ushort x, const t_ushort y)
{
	t_ushort	i;

	i = 0;
	while (i < COUNT_PAIRS - 1)
	{
		if (symbol == env->map[i].key)
		{
			mlx_put_image_to_window(env->mlx, env->main_win.ptr,
				env->images.other.ptr[i], x * env->game.size_pixels,
				y * env->game.size_pixels);
			return (true);
		}
		++i;
	}
	if (symbol == env->map[SymbolStartPosition].key)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.character.ptr[PositionUp],
			x * env->game.size_pixels, y * env->game.size_pixels);
		env->game.x = x;
		env->game.y = y;
		return (true);
	}
	else
		return (false);
}

bool	ft_fill_map(t_environment	*env)
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
			if (ft_handler_symbols(env, env->file.lines[i][j], j, i) == false)
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

bool	ft_main_fill(t_environment	*env)
{
	int	x;
	int	y;

	if (env == NULL)
		return (false);
	if (ft_create_mlx(env) == false)
		return (false);
	env->game.size_pixels = ft_calc_size_pixel(*env, 128);
	if (env->game.size_pixels == 0)
		return (false);
	env->main_win.width = env->game.size_pixels * env->file.length;
	env->main_win.height = env->game.size_pixels * env->file.count;
	if (ft_fill_paths(&env->paths, env->game.size_pixels) == false
		|| ft_fill_images(env, &x, &y) == false)
		return (false);
	if (x != 600 || y != 400)
		return (false);
	env->main_win.ptr = mlx_new_window(env->mlx, env->main_win.width,
			env->main_win.height, "So_long");
	if (ft_fill_map(env) == false)
		return (false);
	return (true);
}
