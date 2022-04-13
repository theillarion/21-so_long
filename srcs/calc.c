#include "so_long.h"

t_ushort	ft_calc_size_pixel(const t_environment env, t_ushort min_size_pixel,
	t_ushort	max_size_pixel)
{
	t_ushort	pixel_min;
	t_ushort	pixel_x;
	t_ushort	pixel_y;

	pixel_x = env.main_win.width / env.file.length;
	pixel_y = env.main_win.height / env.file.count;
	if (pixel_x <= pixel_y)
		pixel_min = pixel_x;
	else
		pixel_min = pixel_y;
	if (pixel_min < min_size_pixel)
		return (0);
	while (max_size_pixel > pixel_min)
		max_size_pixel = max_size_pixel >> 1;
	return (max_size_pixel);
}

size_t	ft_calc_discharge(long long number)
{
	if (number <= 9 && number >= -9)
		return (1);
	else
		return (1 + ft_calc_discharge(number / 10));
}
