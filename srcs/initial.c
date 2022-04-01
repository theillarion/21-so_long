#include "so_long.h"

static void	ft_initial_pair(t_pair	*map)
{
	t_ushort	i;

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
}

static void ft_initual_game(t_game	*game)
{
	if (game == NULL)
		return ;
	game->size_pixels = 0;
	game->x = 0;
	game->y = 0;
	game->is_action = false;
	game->current_position = PositionUp;
	game->next_position = PositionUp;
}

bool	ft_main_initial(t_environment	*env)
{
	if (env == NULL)
		return (false);
	env->mlx = mlx_init();
	ft_initial_file(&env->file);
	env->count_uniq_map = COUNT_PAIRS;
	ft_initial_pair(env->map);
	ft_initial_window(&env->main_win);
	ft_initial_window(&env->game_over_win);
	ft_initual_game(&env->game);
	mlx_get_screen_size(env->mlx, (int *)&env->main_win.width,
		(int *)&env->main_win.height);
	env->main_win.height *= 0.9;
	if (env->main_win.width == 0 || env->main_win.height == 0)
		return (false);
	return (true);
}
