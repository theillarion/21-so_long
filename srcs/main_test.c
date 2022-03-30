#include "so_long.h"
//#include <stdbool.h>
//#include <math.h>
/*
#define SCREEN_WIDTH 1408
#define SCREEN_HEIGHT 832

typedef struct	s_vars
{
	void	*mlx;
	void	*window;
	bool	is_true;
	int		x;
	int		y;
	int		step;
	void	*image_wall;
	void	**image;
	int		position;
	
}				t_vars;
*/

int ft_destroy(t_environment	*env)
{
	mlx_destroy_window(env->mlx, env->game_w.ptr);
	mlx_destroy_display(env->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int ft_close_with_key(int keycode, t_environment	*env)
{
	ft_putstr_fd("Press KEY: ", STDOUT_FILENO);
	ft_putnbr_fd(keycode, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (keycode == ESC)
		ft_destroy(env);
	else if (keycode >= LEFT && keycode <= DOWN)
	{
		env->game_w.is_action = true;
		env->game_w.next_position = keycode - LEFT;
	}
	return (0);
}

/* int ft_close_with_key(int keycode, t_vars	*vars)
{
	ft_putstr_fd("Press KEY: ", STDOUT_FILENO);
	ft_putnbr_fd(keycode, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		exit(EXIT_SUCCESS);
	}
	else if (keycode >= LEFT && keycode <= DOWN)
	{
		vars->is_true = true;
		vars->step = keycode - LEFT;
	}
	return (0);
}

int ft_destroy(t_vars	*vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	exit(EXIT_SUCCESS);
	return (0);
} */
/*
bool	ft_push_images(t_environment	*env)
{
	if (env != NULL)
	{
		env->main_images.images[EMPTY_SPACE] = mlx_xpm_file_to_image(env->mlx, "images/empty_space.xpm", NULL, NULL);
	}
	return (false);
}
*/
void	fd_to_do(t_environment	*env, int	*x, int	*y)
{
	
	if (env->game_w.current_position == PositionUp
		&& *y - env->game_w.size_pixels >= 0)
		*y -= env->game_w.size_pixels;
	else if (env->game_w.current_position == PositionDown
		&& *y + env->game_w.size_pixels < env->game_w.height)
		*y += env->game_w.size_pixels;
	else if (env->game_w.current_position == PositionLeft
		&& *x - env->game_w.size_pixels >= 0)
		*x -= env->game_w.size_pixels;
	else if (env->game_w.current_position == PositionRight
		&& *x + env->game_w.size_pixels < env->game_w.width)
		*x += env->game_w.size_pixels;
}

/* int	render_next_frame(t_vars	*vars)
{
	if (vars->is_true)
	{
		mlx_do_sync(vars->mlx);
		ft_putstr_fd("GGG: ", STDOUT_FILENO);
		ft_putnbr_fd(vars->step, STDOUT_FILENO);
		if (vars->position != vars->step)
		{
			ft_putnbr_fd(vars->step, STDOUT_FILENO);
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image[vars->step], vars->x, vars->y);
			vars->position = vars->step;
		}
		else
		{
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image_wall, vars->x, vars->y);
			fd_to_do(vars);
			mlx_put_image_to_window(vars->mlx, vars->window, vars->image[vars->position], vars->x, vars->y);
		}
		
		vars->is_true = false;
	}

	return (0);
} */

int	render_next_frame(t_environment	*env)
{
	int	x;
	int	y;

	if (env != NULL && env->game_w.is_action)
	{
		mlx_do_sync(env->mlx);
		x = env->game_w.x * env->game_w.size_pixels;
		y = env->game_w.y * env->game_w.size_pixels;
		if (env->game_w.current_position != env->game_w.next_position)
		{
			mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.character.ptr[env->game_w.next_position], x, y);
			env->game_w.current_position = env->game_w.next_position;
		}
		else
		{
			mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.other.ptr[SymbolWall], x, y);
			fd_to_do(env, &x, &y);
			mlx_put_image_to_window(env->mlx, env->game_w.ptr, env->images.character.ptr[env->game_w.current_position], x, y);
		}
		env->game_w.is_action = false;
	}

	return (0);
}


int	main(int argc, char	**argv)
{
	(void)argc;
	(void)argv;
	//t_vars	vars;

	t_environment	env;

	if (argc == 2)
	{
		if (ft_main_initial(&env) == false)
			ft_fail(&env, "Error\n", false);
		errno = 0;
		if (ft_get_file(&env.file, argv[1]) == false)
			ft_fail(&env, "Error\nprogram", true);
		else
		{
			if (ft_validation(&env) == false)
				ft_fail(&env, "Error\ninvalid arguments", false);
			else
			{
				if (ft_main_fill(&env) == false)
					ft_fail(&env, "Error\nGGGG", false);
				
				mlx_hook(env.game_w.ptr, KeyPress | KeyRelease, KeyPressMask | KeyReleaseMask, ft_close_with_key, &env);
				mlx_hook(env.game_w.ptr, DestroyNotify, ButtonReleaseMask, ft_destroy, &env);

				mlx_loop_hook(env.mlx, render_next_frame, &env);
				mlx_loop(env.mlx);
			}
				//ft_success(&env, "Success!");
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putendl_fd("Error", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
/*
	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, World!");

	char	str[] = "/home/illarion/test_image/result_xpm/Dirt_64.xpm";
	char	str2[] = "/home/illarion/test_image/result_xpm/Full_64.xpm";
	char	str2_2[] = "/home/illarion/test_image/result_xpm/Full_2_64.xpm";
	char	str2_3[] = "/home/illarion/test_image/result_xpm/Full_3_64.xpm";
	char	str2_4[] = "/home/illarion/test_image/result_xpm/Full_4_64.xpm";

	char	wall[] = "/home/illarion/test_image/result_xpm/Full___64.xpm";

	int width;
	int height;

	vars.image = (void **)malloc((5) * sizeof(*vars.image));

	vars.image_wall = mlx_xpm_file_to_image(vars.mlx, str, &width, &height);
	vars.image[PositionUp] = mlx_xpm_file_to_image(vars.mlx, str2, &width, &height);
	vars.image[PositionRight] = mlx_xpm_file_to_image(vars.mlx, str2_2, &width, &height);
	vars.image[PositionDown] = mlx_xpm_file_to_image(vars.mlx, str2_3, &width, &height);
	vars.image[PositionLeft] = mlx_xpm_file_to_image(vars.mlx, str2_4, &width, &height);

	void	*wall_adrs = mlx_xpm_file_to_image(vars.mlx, wall, &width, &height);

	int g = 0;
	while (g != 4)
	{
		printf("%p\n", vars.image[g]);
		g++;
	}

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
	
	i = 0;

	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			if (i == 0 || j == 0 || i == (SCREEN_WIDTH / 64) - 1 || j == (SCREEN_HEIGHT / 64) - 1)
				mlx_put_image_to_window(vars.mlx, vars.window, wall_adrs, i * 64, j * 64);
			++j;
		}
		++i;
	}

	vars.x = 320;
	vars.y = 320;
	vars.is_true = false;
	vars.position = PositionUp;

	mlx_put_image_to_window(vars.mlx, vars.window, vars.image[PositionUp], vars.x + 16, vars.y);
	mlx_do_sync(vars.mlx);

	mlx_hook(vars.window, KeyPress | KeyRelease, KeyPressMask | KeyReleaseMask, ft_close_with_key, &vars);
	mlx_hook(vars.window, DestroyNotify, ButtonReleaseMask, ft_destroy, &vars);

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);

	return (0);*/
}
