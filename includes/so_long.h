/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <illarion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:53:20 by glashli           #+#    #+#             */
/*   Updated: 2022/06/25 13:09:06 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <time.h>
# include <stdlib.h>

# include "mlx.h"
# include "libft.h"
# include "images.h"

# define SPEED_ENEMY 5000

# ifdef CURRENT_OS_LINUX

enum	e_keys
{
	KeyEsc		= 65307,
	KeyLeft		= 97,
	KeyUp		= 119,
	KeyRight	= 100,
	KeyDown		= 115
};

# else
#  ifdef CURRENT_OS_MACOS

enum	e_keys
{
	KeyEsc		= 53,
	KeyLeft		= 0,
	KeyUp		= 13,
	KeyRight	= 2,
	KeyDown		= 1
};
#  else

enum	e_keys
{
	KeyEsc		= 0,
	KeyLeft		= 0,
	KeyUp		= 0,
	KeyRight	= 0,
	KeyDown		= 0
};
#  endif
# endif

# define COUNT_PAIRS		6
# define BUFFER_SIZE		1024

# define COLOR_LGREEN	"\033[92m"
# define NOCOLOR		"\033[0m"

typedef unsigned short	t_ushort;

enum e_events
{
	KeyPress		= 2,
	KeyRelease		= 3,
	DestroyNotify	= 17
};

enum e_events_mask
{
	KeyPressMask		= (1L<<0),
	KeyReleaseMask		= (1L<<1),
	ButtonReleaseMask	= (1L<<3)
};

enum e_position
{
	PositionLeft,
	PositionUp,
	PositionRight,
	PositionDown,
};

typedef struct s_axis
{
	int x;
	int y;
}		t_axis;

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

typedef struct s_objects
{
	t_array	character;
	t_array	enemy;
	t_array	other;
	t_array	score;
	t_array	destroy;
}	t_objects;

typedef struct s_player
{
	int			x;
	int			y;
	t_ushort	current_position;
	t_ushort	next_position;
}		t_player;

typedef struct s_game
{
	t_ushort	size_pixels;
	t_player	hero;
	t_player	**enemy;
	t_ushort	hero_number;
	bool		is_hero;
	bool		is_action;
	bool		is_end_game;
	bool		is_destroy;
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
	t_objects	images;
	t_objects	paths;
	t_pair		map[COUNT_PAIRS];
}	t_environment;

//				array.c
void			ft_initial_array(t_array	*array);
void			ft_deinitial_array(void	*mlx, t_array	*array,
					int (*ft_clean)(void *, void *));
void			ft_push_copy(t_array	*array, const void	*elem);
void			ft_push_move(t_array	*array, void	*elem);

//				axis.c
t_axis			ft_create_axis(int x, int y);

//				calc.c
t_ushort		ft_calc_size_pixel(const t_environment env,
					t_ushort min_size_pixel, t_ushort	max_size_pixel);
size_t			ft_calc_discharge(long long number);

//				check_step.c
bool			ft_check_step(t_environment	*env, int	*x, int	*y,
					t_ushort	current_position);

//				create.c
bool			ft_create_mlx(t_environment	*env);

//				deinitial.c
int				ft_deinitial_mlx(t_environment	*env);
void			ft_main_deinitial(t_environment	*env);

//				destroy.c
void			ft_destroy_display(void	**ptr);
void			ft_destroy_hero(t_environment	*env);

//				event.c
int				ft_event_key_press(int keycode, t_environment	*env);
int				ft_event_key_release(int keycode, t_environment	*env);

//				exit.c
void			ft_fail(t_environment	*env, const char	*msg_err,
					bool is_errno);
int				ft_success(t_environment	*env);
void			ft_exit_fail(const char	*msg_err);

//				fill.c
bool			ft_main_fill(t_environment	*env);

//				fill_paths.c
bool			ft_fill_paths(t_objects	*paths, t_ushort	size_pixels);

//				fill_window.c
bool			ft_fill_window(t_environment	*env);
void			ft_fill_status_bar(t_environment	*env);
void			ft_set_size_window(t_environment	*env);

//				free.c
void			ft_smart_free(void	**memory);

//				game_over.c
void			ft_game_over(t_environment	*env);

//				get.c
char			*ft_get_main_directory(t_ushort	size_pixels);
int				ft_get_number_with_count(int number, int count);

//				initial.c
bool			ft_main_initial(t_environment	*env);

//				main.c
int				main(int argc, char	**argv);

//				map.c
short			ft_symbol_to_int(const t_pair	*map, const char symbol);

//				put.c
void			ft_putnbr_in_window(t_environment	*env, size_t number,
					int width, int axisY);
void			ft_putend_with_color_fd(const char	*color,
					const char	*message, int fd7);

//				read_file.c
bool			ft_get_file(t_file	*file, const char	*path);

//				render_game.c
int				ft_render_next_frame(t_environment	*env);

//				render_status_bar.c
void			ft_render_status_bar(t_environment	*env);

//				screen.c
void			ft_get_size_screen(void *mlx_ptr, int *width, int *height);

//				sync.c
void			ft_do_sync(void	*mlx_ptr);

//				validation.c
bool			ft_validation(t_environment	*env);

#endif