#include "so_long.h"

int	ft_event_key_press(int keycode, t_environment	*env)
{
	if (env == NULL || env->game.is_end_game)
		return (EXIT_FAILURE);
	else if (keycode == KeyLeft || keycode == KeyUp || keycode == KeyRight
		||keycode == KeyDown)
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

int	ft_event_key_release(int keycode, t_environment	*env)
{
	if (env == NULL)
		return (EXIT_FAILURE);
	else if (keycode == KeyEsc)
		ft_success(env);
	return (EXIT_SUCCESS);
}
