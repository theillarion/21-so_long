/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status_bar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:53 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:53:59 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		ft_putnbr_in_window(env, ft_get_number_with_count(9, count_cell), width,
			env->main_win.status_bar.start_y);
		return (false);
	}
	else
		ft_putnbr_in_window(env, number, width,
			env->main_win.status_bar.start_y);
	return (true);
}

void	ft_render_status_bar(t_environment	*env)
{
	static size_t	i = 1;
	static bool		is_overflow = false;

	if (!is_overflow)
	{
		if (i == SIZE_MAX)
			is_overflow = true;
		else if (!ft_check_overflow(env, i))
			is_overflow = true;
		else
		{
			ft_putnbr_fd(i, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			++i;
		}
	}
}
