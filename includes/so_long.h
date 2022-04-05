#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <stdint.h>
# include <math.h>

# include "libft.h"

# include "../lib/minilibx-macos/mlx.h"

# define COUNT_PAIRS 5
# define BUFFER_SIZE 1024
# define HEIGHT_STATUS_BAR 16

typedef unsigned short	t_ushort;

enum e_events
{
	KeyPress 		= 2,
	KeyRelease		= 3,
	DestroyNotify	= 17
};

enum e_events_mask
{
	KeyPressMask		= (1L<<0),
	KeyReleaseMask		= (1L<<1),
	ButtonReleaseMask	= (1L<<3)
};

/*enum e_keys
{
	KeyEsc		= 65307,
	KeyLeft		= 97,
	KeyUp		= 119,
	KeyRight	= 100,
	KeyDown		= 115
};*/

enum e_keys
{
	KeyEsc		= 53,
	KeyLeft		= 0,
	KeyUp		= 13,
	KeyRight	= 2,
	KeyDown		= 1
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
	SymbolStartPosition,
	CountSymbols
};

enum e_images_score
{
	Image0,
	Image1,
	Image2,
	Image3,
	Image4,
	Image5,
	Image6,
	Image7,
	Image8,
	Image9,
	ImageWordScore,
	ImageIdle,
	CountImages,
	HeightNumberImage	= 16,
	WidthNumberImage	= 16,
	HeightWordImage		= 16,
	WidthWordImage		= 80
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
	void	*game_over;
	void	*numbers[CountImages];
}	t_images;

typedef struct s_paths
{
	t_array	path_to_character;
	t_array	path_to_other;
	void	*path_to_game_over;
}	t_paths;

typedef struct s_game
{
	t_ushort	size_pixels;
	t_ushort	x;
	t_ushort	y;
	t_ushort	current_position;
	t_ushort	next_position;
	t_ushort	start_position_score;
	bool		is_action;
	bool		is_end_game;
}		t_game;

typedef struct s_window
{
	void		*ptr;
	t_ushort	start_x;
	t_ushort	start_y;
	t_ushort	width;
	t_ushort	height;
	t_ushort	common_width;
	t_ushort	common_height;
	bool		is_used_status_bar;
	struct	s_status_bar
	{
		t_ushort	start_x;
		t_ushort	start_y;
		t_ushort	width;
		t_ushort	height;
	}	status_bar;
}		t_window;
typedef struct s_environment
{
	void		*mlx;
	t_window	main_win;
	t_window	game_over_win;
	t_game		game;
	t_file		file;
	t_images	images;
	t_paths		paths;
	t_pair		map[CountSymbols];
	size_t		count_uniq_map;
}	t_environment;

//			main.c
int			main(int argc, char	**argv);

//			initial.c
void		ft_initial_images(t_images	*images);
void		ft_initial_paths(t_paths	*paths);
bool		ft_main_initial(t_environment	*env);

//			deinitial.c
int			ft_deinitial_mlx(t_environment	*env);
void		ft_main_deinitial(t_environment	*env);

//			exit.c
void		ft_fail(t_environment	*env, const char	*msg_err,
				bool is_errno);
int			ft_success(t_environment	*env);

//			action.c
void		ft_render_status_bar(t_environment	*env);
int			ft_action_key_press(int keycode, t_environment	*env);
int			ft_action_key_release(int keycode, t_environment	*env);

//			render.c
int			render_next_frame(t_environment	*env);

//			free.c
void		ft_smart_free(void	**memory);

//			get.c
char		*ft_get_main_directory(t_ushort	size_pixels);
int 		ft_get_number_with_count(int number, int count);

//			create.c
bool		ft_create_mlx(t_environment	*env);

//			fill.c
bool		ft_main_fill(t_environment	*env);

//			read_file.c
bool		ft_get_file(t_file	*file, const char	*path);

//			validation.c
bool		ft_validation(t_environment	*env);

//			array.c
void		ft_initial_array(t_array	*array);
void		ft_deinitial_array(t_array	*array);
void		ft_push_copy(t_array	*array, const void	*elem);
void		ft_push_move(t_array	*array, void	*elem);

//			game_over.c
void		ft_game_over(t_environment	*env);

//			calc.c
t_ushort	ft_calc_size_pixel(const t_environment env,
				t_ushort	size_pixel);
size_t		ft_calc_discharge(int number);

#endif