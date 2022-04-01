#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <stdint.h>

# include "libft.h"

# include "mlx.h"
# include "mlx_int.h"

# define SCREEN_WIDTH 1408
# define SCREEN_HEIGHT 832
# define COUNT_PAIRS 5
# define BUFFER_SIZE 1024

typedef unsigned short	t_ushort;

enum e_keys
{
	ESC		= 65307,
	LEFT	= 65361,
	UP		= 65362,
	RIGHT	= 65363,
	DOWN	= 65364
};

enum e_position
{
	PositionLeft,
	PositionUp,
	PositionRight,
	PositionDown,
};

enum e_symbols_map
{
	SymbolIdle,
	SymbolWall,
	SymbolCollectible,
	SymbolExit,
	SymbolStartPosition
};

typedef struct s_file
{
	char	**lines;
	size_t	length;
	size_t	count;
}			t_file;
typedef struct s_pair
{
	char			key;
	unsigned int	value;
}					t_pair;

typedef struct s_array
{
	void		**ptr;
	t_ushort	count;
}	t_array;

typedef struct s_images
{
	t_array	character;
	t_array	other;
	void	*wall;
	void	*idle;
	void	*collectible;
	void	*exit;
}	t_images;

typedef struct s_paths
{
	t_array	path_to_character;
	t_array	path_to_other;
	void	*path_to_wall;
	void	*path_to_idle;
	void	*path_to_collectible;
	void	*path_to_exit;
}	t_paths;

typedef struct s_window
{
	void		*ptr;
	t_ushort	width;
	t_ushort	height;
	t_ushort	size_pixels;
	t_ushort	x;
	t_ushort	y;
	t_ushort	current_position;
	t_ushort	next_position;
	bool		is_action;
}		t_window;
typedef struct s_environment
{
	void		*mlx;
	t_window	game_w;
	t_file		file;
	t_images	images;
	t_paths		paths;
	t_pair		map[COUNT_PAIRS];
	size_t		count_uniq_map;
}	t_environment;

//		main.c
int			main(int argc, char	**argv);

//			initial.c
void		ft_initial_array(t_array	*array);
bool		ft_main_initial(t_environment	*env);

//			exit.c
void		ft_fail(t_environment	*env, const char	*msg_err,
				bool is_errno);
void		ft_success(t_environment	*env, const char	*msg);
int			ft_destroy(t_environment	*env);

//			render.c
int			ft_close_with_key(int keycode, t_environment	*env);
int			render_next_frame(t_environment	*env);

//			free.c
void		ft_smart_free(void	**memory);

//			get.c
char		*ft_get_main_directory(t_ushort	size_pixels);

//			fill.c
bool		ft_main_fill(t_environment	*env);

//			read_file.c
bool		ft_get_file(t_file	*file, const char	*path);

//			validation.c
bool		ft_validation(t_environment	*env);

//			array.c
void		ft_push_back(t_array	*array, const void	*elem);
void		ft_delete_all(t_array	*array);
void		ft_push_adrs(t_array	*array, void	*elem);

//		calc.c
t_ushort	ft_calc_size_pixel(const t_environment env,
				t_ushort	size_pixel);

#endif