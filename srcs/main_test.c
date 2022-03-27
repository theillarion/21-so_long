#include "so_long.h"
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

typedef struct s_test
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;
}	t_test;

typedef struct	s_data
{
	void	*image;
	void	*image2;
	void	*image3;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*window;
	t_test	test;
	t_data	img;
	bool	is_true;
	int		x;
	int		y;
	int		step_x;
	int		step_y;
	void	*image_wall;
	void	**image;
	int		position;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
	PositionUp,
	PositionRight,
	PositionDown,
	PositionLeft,
};

int ft_close_with_key(int keycode, t_vars	*vars)
{
	ft_putstr_fd("Press KEY: ", STDOUT_FILENO);
	ft_putnbr_fd(keycode, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		exit(EXIT_SUCCESS);
	}
	if (keycode == LEFT || keycode == UP || keycode == RIGHT || keycode == DOWN)
	{
		vars->is_true = true;
		if (keycode == LEFT)
			vars->step_x = -64;
		if (keycode == UP)
			vars->step_y = -64;
		if (keycode == RIGHT)
			vars->step_x = 64;
		if (keycode == DOWN)
			vars->step_y = 64;
	}
	return (0);
}

int ft_destroy(t_vars	*vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	exit(EXIT_SUCCESS);
	return (0);
}

bool	ft_push_images(t_environment	*env)
{
	if (env != NULL)
	{
		env->main_images.images[EMPTY_SPACE] = mlx_xpm_file_to_image(env->mlx, "images/empty_space.xpm", NULL, NULL);
	}
	return (false);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	render_next_frame(t_vars	*vars)
{
	if (vars->is_true)
	{
		mlx_do_sync(vars->mlx);

		if (vars->step_y == 64 && vars->position != PositionDown )
		{
			ft_putendl_fd("Down", STDOUT_FILENO);
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image[PositionDown], vars->x, vars->y);
			vars->position = PositionDown;
		}
		else if (vars->step_y == -64 && vars->position != PositionUp )
		{
			ft_putendl_fd("Up", STDOUT_FILENO);
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image[PositionUp], vars->x, vars->y);
			vars->position = PositionUp;
		}
		else if (vars->step_x == 64 && vars->position != PositionRight )
		{
			ft_putendl_fd("Right", STDOUT_FILENO);
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image[PositionRight], vars->x, vars->y);
			vars->position = PositionRight;
		}
		else if (vars->step_x == -64 && vars->position != PositionLeft )
		{
			ft_putendl_fd("Left", STDOUT_FILENO);
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image[PositionLeft], vars->x, vars->y);
			vars->position = PositionLeft;
		}
		else
		{
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image_wall, vars->x, vars->y);

			if (vars->y + vars->step_y < SCREEN_WIDTH && vars->y + vars->step_y >= 0)
				vars->y += vars->step_y;

			if (vars->x + vars->step_x < SCREEN_HEIGHT && vars->x + vars->step_x >= 0)
				vars->x += vars->step_x;

			mlx_put_image_to_window(vars->mlx, vars->window, vars->image[vars->position], vars->x, vars->y);
		}
		
		vars->is_true = false;
		vars->step_x = 0;
		vars->step_y = 0;
	}

	return (0);
}

int	main(int argc, char	**argv)
{
	(void)argc;
	(void)argv;
	t_vars	vars;

	vars.test.start_x = 0;
	vars.test.start_y = 0;
	vars.test.end_x = 10;
	vars.test.end_y = 10;

	//mlx_get_screen_size(vars.mlx, &x, &y);

	//printf("%d and %d\n", x, y);
	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");
	vars.img.image = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.image, &vars.img.bits_per_pixel, &vars.img.line_length,
								&vars.img.endian);
	
	/*int i = 0;
	while (i != 100)
	{
		my_mlx_pixel_put(&image, i, i, create_trgb(100, 128, 255, 0));
		++i;
	}*/

	//mlx_put_image_to_window(vars.mlx, vars.window, vars.image.image, 0, 0);

	//char	str[] = "/home/illarion/Загрузки/ILTQq.xpm";

	char	str[] = "/home/illarion/test_image/result_xpm/Dirt_64.xpm";
	char	str2[] = "/home/illarion/test_image/result_xpm/Full_64.xpm";
	char	str2_2[] = "/home/illarion/test_image/result_xpm/Full_2_64.xpm";
	char	str2_3[] = "/home/illarion/test_image/result_xpm/Full_3_64.xpm";
	char	str2_4[] = "/home/illarion/test_image/result_xpm/Full_4_64.xpm";

	int width;
	int height;

	vars.image = (void **)malloc((5) * sizeof(*vars.image));

	vars.image_wall = mlx_xpm_file_to_image(vars.mlx, str, &width, &height);
	vars.image[PositionUp] = mlx_xpm_file_to_image(vars.mlx, str2, &width, &height);
	vars.image[PositionRight] = mlx_xpm_file_to_image(vars.mlx, str2_2, &width, &height);
	vars.image[PositionDown] = mlx_xpm_file_to_image(vars.mlx, str2_3, &width, &height);
	vars.image[PositionLeft] = mlx_xpm_file_to_image(vars.mlx, str2_4, &width, &height);

	int g = 0;
	while (g != 4)
	{
		printf("%p\n", vars.image[g]);
		g++;
	}
	//vars.img.image3 = mlx_xpm_file_to_image(vars.mlx, str3, &width, &height);

	/*if (vars.img.image == NULL)
	{
		printf("Error image\n");
		exit(EXIT_FAILURE);
	}*/

	//printf("Wigth = %d\nHeight%d\n", width, height);

	int i = 0;
	int j = 0;
	int step = 64;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			mlx_put_image_to_window(vars.mlx, vars.window, vars.image_wall, i, j);
			j += step;
		}
		i += step;
	}

	/*i = 0;
	while (i != SCREEN_WIDTH)
	{
		mlx_put_image_to_window(vars.mlx, vars.window, vars.image2, i, 320);
		i += step;
	}*/
	
	vars.x = 320;
	vars.y = 320;
	vars.is_true = false;
	vars.position = PositionUp;

	mlx_put_image_to_window(vars.mlx, vars.window, vars.image[PositionUp], vars.x, vars.y);
	mlx_do_sync(vars.mlx);

	//mlx_put_image_to_window(vars.mlx, vars.window, vars.img.image2, 320, 320);
	//mlx_put_image_to_window(vars.mlx, vars.window, vars.img.image3, 0, 0);

	mlx_hook(vars.window, KeyPress | KeyRelease, KeyPressMask | KeyReleaseMask, ft_close_with_key, &vars);
	//mlx_hook(vars.window, KeyRelease, KeyReleaseMask, ft_close_with_key, &vars);
	mlx_hook(vars.window, DestroyNotify, ButtonReleaseMask, ft_destroy, &vars);

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
