#include "so_long.h"

void	ft_putnbr_in_window(t_environment	*env, size_t number, int width,
			int axisY)
{
	if (number <= 9)
		mlx_put_image_to_window(env->mlx, env->main_win.ptr,
			env->images.score.ptr[number], width, axisY);
	else
	{
		ft_putnbr_in_window(env, number / 10, width - WidthImageNumber, axisY);
		ft_putnbr_in_window(env, number % 10, width, axisY);
	}
}

void	ft_putend_with_color_fd(const char	*color, const char	*message,
	int fd)
{
	if (fd <= 0 || color == NULL || message == NULL)
		return ;
	ft_putstr_fd((char *)color, STDOUT_FILENO);
	ft_putstr_fd((char *)message, STDOUT_FILENO);
	ft_putendl_fd(NOCOLOR, STDOUT_FILENO);
}
