/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:53:11 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:53:16 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifdef CURRENT_OS_LINUX

void	ft_do_sync(void	*mlx_ptr)
{
	mlx_do_sync(mlx_ptr);
}
#else

void	ft_do_sync(void	*mlx_ptr)
{
	(void)mlx_ptr;
}
#endif