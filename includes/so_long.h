#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

# include "libft.h"

# include "pair.h"

# include "mlx.h"
# include "mlx_int.h"

# define COUNT_PAIRS 5
# define BUFFER_SIZE 1024

enum e_symbols_map
{
	EMPTY_SPACE,
	WALL,
	COLLECTIBLE,
	EXIT,
	START_POSITION
};

typedef struct s_file
{
	char	**lines;
	size_t	length;
	size_t	count;
}			t_file;

typedef struct s_images
{
	void	**images;
	size_t	count;
}	t_images;
typedef struct s_environment
{
	void		*mlx;
	void		*window;
	t_images	main_images;
	t_file		file;
	t_pair		map[COUNT_PAIRS];
	size_t		count_uniq_map;
}	t_environment;

int	main(int argc, char	**argv);

void	ft_initial_struct_pair(t_pair	*map);
void	ft_initial_struct_file(t_file	*file);
void	ft_main_initial(t_environment	*env);

void	ft_fail(t_environment	*env, const char	*msg_err, bool is_errno);
void	ft_success(t_environment	*env, const char	*msg);

void	ft_smart_free(void	**memory);

bool	ft_get_file(t_file	*file, const char	*path);

size_t	ft_convert_to_index(const char key);

bool	ft_validation(t_environment	*env);

#endif