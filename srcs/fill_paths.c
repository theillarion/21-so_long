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

static void	ft_fill_paths_range(t_array	*array, const char	*basedir,
	const char	*dir, u_short	i_max)
{
	char	*full_dir;
	u_short	i;

	if (basedir == NULL)
		full_dir = ft_strdup(dir);
	else
		full_dir = ft_strjoin(basedir, dir);
	i = 0;
	while (i < i_max)
	{
		ft_push_move(array, ft_get_name(full_dir, ".xpm", (int)i));
		++i;
	}
	ft_smart_free((void **)&full_dir);
}

static void	ft_fill_all_paths(t_objects *paths, const char	*dir)
{
	ft_push_move(&paths->character, ft_strjoin(dir,
			"character/character_left.xpm"));
	ft_push_move(&paths->character, ft_strjoin(dir,
			"character/character_up.xpm"));
	ft_push_move(&paths->character, ft_strjoin(dir,
			"character/character_right.xpm"));
	ft_push_move(&paths->character, ft_strjoin(dir,
			"character/character_down.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_left.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_up.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_right.xpm"));
	ft_push_move(&paths->enemy, ft_strjoin(dir, "enemy/enemy_down.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "idle/idle.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "wall/wall.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "collectible/collectible.xpm"));
	ft_push_move(&paths->other, ft_strjoin(dir, "exit/exit.xpm"));
	ft_fill_paths_range(&paths->score, NULL, "images/numbers_16/number", 10);
	ft_push_move(&paths->score, ft_strdup("images/word_score_16.xpm"));
	ft_push_move(&paths->score, ft_strdup("images/idle_16.xpm"));
	ft_push_move(&paths->score, ft_strdup("images/game_over_600_x_400.xpm"));
	ft_fill_paths_range(&paths->destroy, dir, "destroy/destroy_", 9);
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
