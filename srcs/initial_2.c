#include "so_long.h"

void	ft_initial_images(t_images	*images)
{
	if (images == NULL)
		return ;
	ft_initial_array(&images->character);
	ft_initial_array(&images->other);
	ft_initial_array(&images->score);
}

void	ft_initial_paths(t_paths	*paths)
{
	if (paths == NULL)
		return ;
	ft_initial_array(&paths->path_to_character);
	ft_initial_array(&paths->path_to_other);
	ft_initial_array(&paths->score);
}
