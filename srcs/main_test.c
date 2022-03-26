#include "so_long.h"
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

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
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

enum e_keys
{
	ESC = 65307
};

int ft_close_with_key(int keycode, t_vars	*vars)
{
	ft_putnbr_fd(keycode, STDOUT_FILENO);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int ft_destroy(t_vars	*vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	exit(EXIT_SUCCESS);
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
	//vars.img.image = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	//vars.img.addr = mlx_get_data_addr(vars.img.image, &vars.img.bits_per_pixel, &vars.img.line_length,
	//							&vars.img.endian);
	
	/*int i = 0;
	while (i != 100)
	{
		my_mlx_pixel_put(&image, i, i, create_trgb(100, 128, 255, 0));
		++i;
	}*/

	//mlx_put_image_to_window(vars.mlx, vars.window, vars.image.image, 0, 0);

	char	str[] = "/home/illarion/Загрузки/ILTQq.xpm";

	int width;
	int height;

	vars.img.image = mlx_xpm_file_to_image(vars.mlx, str, &width, &height);

	printf("Wigth = %d\nHeight%d\n", width, height);

	mlx_put_image_to_window(vars.mlx, vars.window, vars.img.image, 100, 0);

	mlx_hook(vars.window, KeyRelease, KeyReleaseMask, ft_close_with_key, &vars);
	mlx_hook(vars.window, DestroyNotify, ButtonReleaseMask, ft_destroy, &vars);

	//mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
