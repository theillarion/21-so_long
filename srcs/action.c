#include "so_long.h"

void	ft_output_number(t_environment	*env, size_t number, int width, int
axisY)
{
	if (number <= 9)
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.score.ptr[number], width, axisY);
	else
	{
		ft_output_number(env, number / 10, width - WidthImageNumber, axisY);
		ft_output_number(env, number % 10, width, axisY);
	}
}

static bool	ft_check_overflow(t_environment	*env, size_t number)
{
	int	interval;
	int	count_cell;
	int	count_discharge;
	int	width;

	interval = env->main_win.width - env->main_win.status_bar.start_x;
	count_cell = (interval / WidthImageNumber);
	count_discharge = (int)ft_calc_discharge((long long)number);
	width = env->main_win.status_bar.start_x
		+ (count_discharge - 1) * WidthImageNumber;
	if (count_discharge > count_cell)
	{
		ft_output_number(env, ft_get_number_with_count(9, count_cell), width,
			env->main_win.status_bar.start_y);
		return (false);
	}	
	else
		ft_output_number(env, number, width, env->main_win.status_bar.start_y);
	return (true);
}

void	ft_render_status_bar(t_environment	*env)
{
	static size_t	i;
	static bool		is_overflow;

	if (!is_overflow)
	{
		if (i == 0)
			i = 1;
		if (i == SIZE_MAX)
			is_overflow = true;
		else if (!ft_check_overflow(env, i))
				is_overflow = true;
		else
			++i;
	}
}

int	ft_action_key_press(int keycode, t_environment	*env)
{
	if (env == NULL)
		return (EXIT_FAILURE);
	else if (env->game.is_end_game != false || keycode == KeyLeft
		|| keycode == KeyUp || keycode == KeyRight || keycode == KeyDown)
	{
		env->game.is_action = true;
		if (keycode == KeyLeft)
			env->game.hero.next_position = PositionLeft;
		else if (keycode == KeyUp)
			env->game.hero.next_position = PositionUp;
		else if (keycode == KeyRight)
			env->game.hero.next_position = PositionRight;
		else
			env->game.hero.next_position = PositionDown;
	}
	return (EXIT_SUCCESS);
}

int	ft_action_key_release(int keycode, t_environment	*env)
{
	if (env == NULL)
		return (EXIT_FAILURE);
	else if (keycode == KeyEsc)
		ft_success(env);
	return (EXIT_SUCCESS);
}
