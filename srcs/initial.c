#include "so_long.h"

static void	ft_initial_pair(t_pair	*map)
{
	u_short	i;

	if (map == NULL)
		return ;
	map[SymbolIdle].key = '0';
	map[SymbolWall].key = '1';
	map[SymbolCollectible].key = 'C';
	map[SymbolExit].key = 'E';
	map[SymbolStartPosition].key = 'P';
	i = 0;
	while (i != COUNT_PAIRS)
		map[i++].value = 0;
}

static void	ft_initial_file(t_file	*file)
{
	if (file == NULL)
		return ;
	file->count = 0;
	file->length = 0;
	file->lines = NULL;
}

static void	ft_initial_window(t_window	*window)
{
	if (window == NULL)
		return ;
	window->ptr = NULL;
	window->width = 0;
	window->height = 0;
	window->size_pixels = 0;
	window->x = 0;
	window->y = 0;
	window->is_action = false;
	window->current_position = PositionUp;
	window->next_position = PositionUp;
}

void	ft_initial_array(t_array	*array)
{
	array->count = 0;
	array->ptr = NULL;
}

bool	ft_main_initial(t_environment	*env)
{
	if (env == NULL)
		return (false);
	env->mlx = mlx_init();
	ft_initial_file(&env->file);
	env->count_uniq_map = COUNT_PAIRS;
	ft_initial_pair(env->map);
	ft_initial_window(&env->game_w);
	mlx_get_screen_size(env->mlx, (int *)&env->game_w.width,
			(int *)&env->game_w.height);
	if (env->game_w.width == 0 || env->game_w.height == 0)
		return (false);
	return (true);
}
