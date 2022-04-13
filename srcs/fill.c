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
		|| !ft_fill_images(env->mlx, &env->paths.character,
			&env->images.character)
		|| !ft_fill_images(env->mlx, &env->paths.other,
			&env->images.other)
		|| !ft_fill_images(env->mlx, &env->paths.score, &env->images.score))
		return (false);
	env->main_win.ptr = mlx_new_window(env->mlx, env->main_win.common_width,
			env->main_win.common_height, "So_long");
	if (ft_fill_window(env) == false)
		return (false);
	if (WidthImageWord + 3 * WidthImageNumber < env->main_win.common_width)
		env->main_win.status_bar.start_x = WidthImageWord + WidthImageNumber;
	ft_fill_status_bar(env);
	return (true);
}
