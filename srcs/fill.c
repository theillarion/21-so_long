#include "so_long.h"

static void ft_fill_paths_character(t_array	*array, const char	*dir)
{
	ft_push_move(array, ft_strjoin(dir,"character/character_left.xpm"));
	ft_push_move(array, ft_strjoin(dir,"character/character_up.xpm"));
	ft_push_move(array, ft_strjoin(dir,"character/character_right.xpm"));
	ft_push_move(array, ft_strjoin(dir,"character/character_down.xpm"));
}

static void ft_fill_paths_other(t_array	*array, const char	*dir)
{
	ft_push_move(array, ft_strjoin(dir, "idle/idle.xpm"));
	ft_push_move(array, ft_strjoin(dir, "wall/wall.xpm"));
	ft_push_move(array,ft_strjoin(dir, "collectible/collectible.xpm"));
	ft_push_move(array, ft_strjoin(dir, "exit/exit.xpm"));
}

static void	*ft_get_name(const char	*filename, const char	*ext, int number)
{
	char	*result;
	char	*buff;

	buff = ft_itoa(number);
	result = ft_strjoin(filename, buff);
	ft_smart_free((void **)&buff);
	buff = result;
	result = ft_strjoin(result, ext);
	ft_smart_free((void **)&buff);
	return (result);
}

static void ft_fill_paths_scores(t_array	*array)
{
	t_ushort	i;
	char		*filename;

	i = 0;
	filename = NULL;
	while (i <= 9)
	{
		filename = ft_get_name("images/numbers_16/number", ".xpm", (int)i);
		ft_push_move(array, (void *)filename);
		filename = NULL;
		++i;
	}
	ft_push_copy(array, "images/word_score_16.xpm");
	ft_push_copy(array, "images/idle_16.xpm");
	ft_push_copy(array, "images/game_over_600_x_400.xpm");
}

bool	ft_fill_paths(t_paths	*paths, t_ushort	size_pixels)
{
	char	*main_dir;

	if (paths == NULL || size_pixels == 0)
		return (false);
	main_dir = ft_get_main_directory(size_pixels);
	ft_fill_paths_character(&paths->path_to_character, main_dir);
	ft_fill_paths_other(&paths->path_to_other, main_dir);
	ft_fill_paths_scores(&paths->score);
	if (main_dir != NULL)
		ft_smart_free((void *)&main_dir);
	return (true);
}

/*
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
*/

bool	ft_fill_images(void	*mlx, const t_array	*src, t_array	*dest)
{
    t_ushort	i;
	int			x;
	int			y;

    if (mlx == NULL || src == NULL || dest == NULL)
        return (false);
    i = 0;
    while (i < src->count)
    {
        ft_push_move(dest, mlx_xpm_file_to_image(mlx,
												 src->ptr[i], &x, &y));
        if (dest->ptr == NULL || dest->ptr[i] == NULL || x == 0 || y == 0)
            return (false);
		++i;
    }
	return (true);
}
/*
bool	fill_images_numbers(t_environment	*env, int	*x, int	*y)
{
	t_ushort	i;
	char		*number;
	char		*path;

	if (env == NULL)
		return (false);
	i = 0;
	while (i < CountImages - 2)
	{
		number = ft_itoa(i);
		path = ft_strjoin("images/numbers_16/number", number);
		ft_smart_free((void	**)&number);
		number = path;
		path = ft_strjoin(path, ".xpm");
		ft_smart_free((void **)&number);
		env->images.numbers[i] = mlx_xpm_file_to_image(env->mlx, path, x, y);
		ft_smart_free((void	**)&path);
		if (env->images.numbers[i++] == NULL ||* x != 16 || *y != 16)
			return (false);
	}
	env->images.numbers[ImageWordScore] = mlx_xpm_file_to_image(env->mlx, "images/word_score_16.xpm", x, y);
	if (env->images.numbers[ImageWordScore] == NULL || *x != 80 || *y != 16)
		return (false);
	env->images.numbers[ImageIdle] = mlx_xpm_file_to_image(env->mlx, "images/idle_16.xpm", x, y);
	if (env->images.numbers[ImageIdle] == NULL || *x != 16 || *y != 16)
		return (false);
	return (true);
}
*/
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
			if (ft_handler_symbols(env, env->file.lines[i][j], j, i) == false)
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
			env->images.score.ptr[ImageWordScore], 0, y);
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
				env->images.score.ptr[ImageIdle], WidthWordImage, y);
	}
	mlx_put_image_to_window(env->mlx, env->main_win.ptr,
		env->images.score.ptr[Image0], x, y);
	x += WidthNumberImage;
	while (x < env->main_win.common_width)
	{
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.score.ptr[ImageIdle], x, y);
		x += WidthNumberImage;
	}
}

void	ft_set_size_window(t_environment	*env)
{
	env->main_win.width = env->game.size_pixels * env->file.length;
	env->main_win.height = env->game.size_pixels * env->file.count;
	env->main_win.status_bar.start_x = 0;
	env->main_win.status_bar.start_y = env->main_win.height;
	env->main_win.status_bar.width = env->main_win.width;
	env->main_win.status_bar.height = HeightWordImage;
	env->main_win.common_width = env->main_win.width;
	env->main_win.common_height = env->main_win.height
		+ env->main_win.status_bar.height;
}

bool	ft_main_fill(t_environment	*env)
{
	if (env == NULL)
		return (false);
	if (ft_create_mlx(env) == false)
		return (false);
	env->game.size_pixels = ft_calc_size_pixel(*env, 128);
	if (env->game.size_pixels == 0)
		return (false);
	ft_set_size_window(env);
	if (ft_fill_paths(&env->paths, env->game.size_pixels) == false
		|| !ft_fill_images(env->mlx, &env->paths.path_to_character, &env->images.character)
		|| !ft_fill_images(env->mlx, &env->paths.path_to_other, &env->images.other)
		|| !ft_fill_images(env->mlx, &env->paths.score, &env->images.score))
		return (false);
	env->main_win.ptr = mlx_new_window(env->mlx, env->main_win.common_width,
			env->main_win.common_height, "So_long");
	if (ft_fill_window(env) == false)
		return (false);
	if (WidthWordImage + 3 * WidthNumberImage < env->main_win.common_width)
		env->main_win.status_bar.start_x = WidthWordImage + WidthNumberImage;
	ft_fill_status_bar(env);
	return (true);
}
