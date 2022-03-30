#include "so_long.h"

u_short	ft_calc_size_pixel(const t_environment env,
		u_short	size_pixel)
{
	u_short	pixel_min;
	u_short	pixel_x;
	u_short	pixel_y;

	pixel_x = env.game_w.width / env.file.length;
	pixel_y = env.game_w.height / env.file.count;
	if (pixel_x <= pixel_y)
		pixel_min = pixel_x;
	else
		pixel_min = pixel_y;
	if (pixel_min < 4)
		return (0);
	while (size_pixel > pixel_min)
		size_pixel = size_pixel >> 1;
	return (size_pixel);
}
