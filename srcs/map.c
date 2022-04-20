/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:43 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:54:25 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

short	ft_symbol_to_int(const t_pair	*map, const char symbol)
{
	if (map[ImageIdle].key == symbol)
		return (ImageIdle);
	else if (map[ImageWall].key == symbol)
		return (ImageWall);
	else if (map[ImageCollectible].key == symbol)
		return (ImageCollectible);
	else if (map[ImageExit].key == symbol)
		return (ImageExit);
	else if (map[ImageEnemy].key == symbol)
		return (ImageEnemy);
	else if (map[ImageStartPosition].key == symbol)
		return (ImageStartPosition);
	return (-1);
}
