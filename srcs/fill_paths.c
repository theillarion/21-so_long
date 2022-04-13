#include "so_long.h"

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

static void	ft_fill_paths_scores(t_array	*array)
{
	t_ushort	i;

	i = 0;
	while (i <= 9)
	{
		ft_push_move(array, ft_get_name("images/numbers_16/number",
										".xpm", (int)i));
		++i;
	}
	ft_push_move(array, ft_strdup("images/word_score_16.xpm"));
	ft_push_move(array, ft_strdup("images/idle_16.xpm"));
	ft_push_move(array, ft_strdup("images/game_over_600_x_400.xpm"));
}

static void	ft_fill_all_paths(t_objects *paths, const char	*dir)
{
	ft_push_move(&paths->character, ft_strjoin(dir, "character/character_left.xpm"));
	ft_push_move(&paths->character, ft_strjoin(dir, "character/character_up.xpm"));
	ft_push_move(&paths->character, ft_strjoin(dir, "character/character_right.xpm"));
	ft_push_move(&paths->character, ft_strjoin(dir, "character/character_down.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_left.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_up.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_right.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_down.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "idle/idle.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "wall/wall.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "collectible/collectible.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "exit/exit.xpm"));
	ft_fill_paths_scores(&paths->score);
}

bool	ft_fill_paths(t_objects	*paths, t_ushort	size_pixels)
{
	char	*main_dir;

	if (paths == NULL || size_pixels == 0)
		return (false);
	main_dir = ft_get_main_directory(size_pixels);
	ft_fill_all_paths(paths, main_dir);
	if (main_dir != NULL)
		ft_smart_free((void **)&main_dir);
	return (true);
}
