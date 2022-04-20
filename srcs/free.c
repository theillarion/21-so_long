/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:31 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:53:50 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	ft_smart_free(void	**memory)
{
	if (memory != NULL && *memory != NULL)
	{
		free(*memory);
		*memory = NULL;
	}
}
