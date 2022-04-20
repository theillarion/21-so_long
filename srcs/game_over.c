/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:33 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:53:51 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_game_over(t_environment	*env)
{
	if (env == NULL || env->game_over_win.ptr != NULL)
		return ;
	env->game.is_end_game = true;
	env->game_over_win.ptr = mlx_new_window(env->mlx, 600, 400, "Game over!");
	mlx_put_image_to_window(env->mlx, env->game_over_win.ptr,
		env->images.score.ptr[ImageScoreGameOver], 0, 0);
	mlx_hook(env->game_over_win.ptr, KeyRelease,
		KeyReleaseMask, ft_event_key_release, env);
	mlx_hook(env->game_over_win.ptr, DestroyNotify,
		ButtonReleaseMask, ft_success, env);
}
