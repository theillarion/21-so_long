#include "so_long.h"

bool	ft_fill_paths(t_paths	*paths, u_short	size_pixels)
{
	char	*main_dir;

	if (paths == NULL || size_pixels == 0)
		return false;
	main_dir = ft_get_main_directory(size_pixels);
	ft_initial_array(&paths->path_to_other);
	ft_push_back(&paths->path_to_other, (void *)ft_strjoin(main_dir, "idle/idle.xpm"));
	ft_push_back(&paths->path_to_other, (void *)ft_strjoin(main_dir, "wall/wall.xpm"));
	ft_push_back(&paths->path_to_other,
		(void *)ft_strjoin(main_dir, "collectible/collectible.xpm"));
	ft_push_back(&paths->path_to_other, (void *)ft_strjoin(main_dir, "exit/exit.xpm"));
	ft_initial_array(&paths->path_to_character);
	ft_push_back(&paths->path_to_character, (void *)ft_strjoin(main_dir,
			"character/character_left.xpm"));
	ft_push_back(&paths->path_to_character, (void *)ft_strjoin(main_dir,
			"character/character_up.xpm"));
	ft_push_back(&paths->path_to_character, (void *)ft_strjoin(main_dir,
			"character/character_right.xpm"));
	ft_push_back(&paths->path_to_character, (void *)ft_strjoin(main_dir,
			"character/character_down.xpm"));
	if (main_dir != NULL)
		ft_smart_free((void *)&main_dir);
	return (true);
}

	//paths->path_to_idle = (void *)ft_strjoin(main_dir, "idle/idle.xpm");
	//paths->path_to_wall = (void *)ft_strjoin(main_dir, "wall/wall.xpm");
	//paths->path_to_collectible = (void *)ft_strjoin(main_dir,
	//		"collectible/collectible.xpm");
	//paths->path_to_exit = (void *)ft_strjoin(main_dir, "exit/exit.xpm");

bool	ft_fill_images(t_environment	*env, u_short x, u_short y)
{
	u_short	i;

	if (env == NULL && env->mlx == NULL && env->game_w.ptr == NULL)
		return (false);
	ft_initial_array(&env->images.other);
	i = 0;
	while (i < env->paths.path_to_other.count)
	{
		ft_push_back(&env->images.other, mlx_xpm_file_to_image(env->mlx,
				env->paths.path_to_other.ptr[i], (int *)&x, (int *)&y));
		if (env->images.other.ptr == NULL || env->images.other.ptr[i++] == NULL
			|| x != env->game_w.size_pixels || y != env->game_w.size_pixels)
			return (false);
	}
	ft_initial_array(&env->images.character);
	i = 0;
	while (i < env->paths.path_to_character.count)
	{
		ft_push_back(&env->images.character, mlx_xpm_file_to_image(env->mlx,
				env->paths.path_to_character.ptr[i], (int *)&x, (int *)&y));
		if (env->images.character.ptr || env->images.character.ptr[i++] == NULL
			|| x != env->game_w.size_pixels || y != env->game_w.size_pixels)
			return (false);
	}
	return (true);
}

	/*env->images.idle = mlx_xpm_file_to_image(env->mlx,
			env->paths.path_to_idle, NULL, NULL);
	env->images.wall = mlx_xpm_file_to_image(env->mlx,
			env->paths.path_to_wall, NULL, NULL);
	env->images.collectible = mlx_xpm_file_to_image(env->mlx,
			env->paths.path_to_collectible, NULL, NULL);
	env->images.exit = mlx_xpm_file_to_image(env->mlx,
			env->paths.path_to_exit, NULL, NULL);*/

static bool	ft_handler_symbols(t_environment	*env, const char symbol,
		const u_short x, const u_short y)
{
	u_short	i;

	i = 0;
	while (i < COUNT_PAIRS - 1)
	{
		if (symbol == env->map[i].key)
		{
			mlx_put_image_to_window(env->mlx, env->game_w.ptr,
				env->images.other.ptr[i], x * env->game_w.size_pixels,
				y * env->game_w.size_pixels);
			return (true);
		}
		++i;
	}
	if (symbol == env->map[SymbolStartPosition].key)
	{
		mlx_put_image_to_window(env->mlx, env->game_w.ptr,
			env->images.character.ptr[PositionUp],
			x * env->game_w.size_pixels, y * env->game_w.size_pixels);
		env->game_w.x = x;
		env->game_w.y = y;
		return (true);
	}
	else
		return (false);
}

/*if (symbol == env->map[SymbolIdle].key)
		mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.idle,
			x * env->game_w.size_pixels, y * env->game_w.size_pixels);
	else if (symbol == env->map[SymbolWall].key)
		mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.wall,
			x * env->game_w.size_pixels, y * env->game_w.size_pixels);
	else if (symbol == env->map[SymbolCollectible].key)
		mlx_put_image_to_window(env->mlx, env->game_w.ptr,
			env->images.collectible,
			x * env->game_w.size_pixels, y * env->game_w.size_pixels);
	else if (symbol == env->map[SymbolExit].key)
		mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.exit,
			x * env->game_w.size_pixels, y * env->game_w.size_pixels);
	else if (symbol == env->map[SymbolStartPosition].key)
		mlx_put_image_to_window(env->mlx, env->game_w.ptr,
			env->images.character.ptr[PositionUp],
			x * env->game_w.size_pixels, y * env->game_w.size_pixels);
	else
		return (false);
	return (true);*/

bool	ft_fill_map(t_environment	*env)
{
	u_short	i;
	u_short	j;

	if (env == NULL)
		return (false);
	i = 0;
	while (i < env->file.length)
	{
		j = 0;
		while (j < env->file.count)
		{
			if (ft_handler_symbols(env, env->file.lines[i][j], i, j) == false)
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}
/*
void	ft_output(const t_paths	*paths)
{
	size_t	i;

	printf("Size character: %d\n", paths->path_to_character.count);
	i = 0;
	if (paths->path_to_character.ptr == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (i < paths->path_to_character.count && paths->path_to_character.ptr[i])
	{
		printf("Elem %%%ld: %s (%p)\n", i, (char *)paths->path_to_character.ptr[i], paths->path_to_character.ptr[i]);
		++i;
	}
	printf("\nSize other: %d\n", paths->path_to_other.count);
	i = 0;
	if (paths->path_to_other.ptr == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (i < paths->path_to_other.count && paths->path_to_other.ptr[i])
	{
		printf("Elem %%%ld: %s (%p)\n", i, (char *)paths->path_to_other.ptr[i], paths->path_to_other.ptr[i]);
		++i;
	}
}*/

bool	ft_main_fill(t_environment	*env)
{
	if (env == NULL || env->mlx == NULL)
		return (false);
	env->game_w.size_pixels = ft_calc_size_pixel(*env, 64);
	if (env->game_w.size_pixels == 0)
			return (false);
	env->game_w.width = env->game_w.size_pixels * env->file.length;
	env->game_w.height = env->game_w.size_pixels * env->file.count;
	if (ft_fill_paths(&env->paths, env->game_w.size_pixels) == false
		|| ft_fill_images(env, 0, 0) == false)
		return (false);
	env->game_w.ptr = mlx_new_window(env->mlx, env->game_w.width,
		env->game_w.height, "So_long");
	if (ft_fill_map(env) == false)
		return (false);
	return (true);
}
