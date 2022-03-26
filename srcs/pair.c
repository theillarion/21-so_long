#include "so_long.h"

size_t	ft_get_value(const t_pair	*map, const char key)
{
	if (key == '0')
		return (map[0].value);
	else if (key == '1')
		return (map[1].value);
	else if (key == 'C')
		return (map[2].value);
	else if (key == 'E')
		return (map[3].value);
	else if (key == 'P')
		return (map[4].value);
	else
		return (SIZE_MAX);
}

size_t	ft_convert_to_index(const char key)
{
	if (key == '0')
		return (EMPTY_SPACE);
	else if (key == '1')
		return (WALL);
	else if (key == 'C')
		return (COLLECTIBLE);
	else if (key == 'E')
		return (EXIT);
	else if (key == 'P')
		return (START_POSITION);
	else
		return (SIZE_MAX);
}
