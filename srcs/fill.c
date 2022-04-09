#include "so_long.h"

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
