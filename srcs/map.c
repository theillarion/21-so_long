#include "so_long.h"

t_ushort	ft_symbol_to_int(const t_pair	*map, const char symbol)
{
	if (map[ImageIdle].key == symbol)
		return (ImageIdle);
	else if (map[ImageWall].key == symbol)
		return (ImageWall);
	else if (map[ImageCollectible].key == symbol)
		return (ImageCollectible);
	else if (map[ImageExit].key == symbol)
		return (ImageExit);
	else if (map[ImageEnemy].key == symbol)
		return (ImageEnemy);
	else if (map[ImageStartPosition].key == symbol)
		return (ImageStartPosition);
	return (0);
}
