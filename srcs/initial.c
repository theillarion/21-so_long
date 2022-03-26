#include "so_long.h"

void	ft_initial_struct_pair(t_pair	*map)
{
	size_t	i;

	if (map != NULL)
	{
		map[EMPTY_SPACE].key = '0';
		map[WALL].key = '1';
		map[COLLECTIBLE].key = 'C';
		map[EXIT].key = 'E';
		map[START_POSITION].key = 'P';
		i = 0;
		while (i != COUNT_PAIRS)
			map[i++].value = 0;
	}
}

void	ft_initial_struct_file(t_file	*file)
{
	if (file != NULL)
	{
		file->count = 0;
		file->length = 0;
		file->lines = NULL;
	}
}

void	ft_main_initial(t_environment	*env)
{
	if (env != NULL)
	{
		ft_initial_struct_file(&env->file);
		ft_initial_struct_pair(env->map);
	}
}