#ifndef PAIR_H
# define PAIR_H

# include <stddef.h> 
# include <stdint.h>

typedef	struct s_pair
{
	char	key;
	size_t	value;
}		t_pair;

size_t	ft_get_value(const t_pair	*map, const char key);

#endif