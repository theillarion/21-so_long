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

static void	ft_initial_window(t_window	*window, bool is_used_status_bar)
{
	if (window == NULL)
		return ;
	window->ptr = NULL;
	window->start_x = 0;
	window->start_y = 0;
	window->width = 0;
	window->height = 0;
	window->common_width = 0;
	window->common_height = 0;
	window->is_used_status_bar = is_used_status_bar;
	if (is_used_status_bar)
	{
		window->status_bar.start_x = 0;
		window->status_bar.start_y = 0;
		window->status_bar.width = 0;
		window->status_bar.height = 0;
	}
}

static void	ft_initial_game(t_game	*game)
{
	if (game == NULL)
		return ;
	game->size_pixels = 0;
	game->x = 0;
	game->y = 0;
	game->is_action = false;
	game->is_end_game = false;
	game->current_position = PositionUp;
	game->next_position = PositionUp;
	game->start_position_score = 0;
}

bool	ft_main_initial(t_environment	*env)
{
	if (env == NULL)
		return (false);
	env->mlx = NULL;
	ft_initial_file(&env->file);
	env->count_uniq_map = CountSymbols;
	ft_initial_pair(env->map);
	ft_initial_paths(&env->paths);
	ft_initial_images(&env->images);
	ft_initial_window(&env->main_win, true);
	ft_initial_window(&env->game_over_win, false);
	ft_initial_game(&env->game);
	return (true);
}
