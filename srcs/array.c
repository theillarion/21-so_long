#include "so_long.h"

void	ft_push_back(t_array	*array, const void	*elem)
{
	void	**ptr;
	t_ushort	i;

	if (array != NULL && elem != NULL)
	{
		ptr = (void **)malloc((array->count + 1) * sizeof(*ptr));
		i = 0;
		while (i < array->count && array->ptr[i])
		{
			ptr[i] = (void *)malloc((ft_strlen(array->ptr[i]) + 1)
					* sizeof(**array->ptr));
			ft_memcpy(ptr[i], array->ptr[i], (ft_strlen(array->ptr[i]) + 1)
				* sizeof(**array->ptr));
			free(array->ptr[i++]);
		}
		ptr[i] = (void *)malloc((ft_strlen((char *)elem) + 1) * sizeof(*elem));
		ft_memcpy(ptr[i], elem, (ft_strlen((char *)elem) + 1) * sizeof(*elem));
		free(array->ptr);
		array->ptr = ptr;
		++array->count;
	}
}

void	ft_push_adrs(t_array	*array, void	*elem)
{
	void	**ptr;
	t_ushort	i;

	if (array != NULL && elem != NULL)
	{
		ptr = (void **)malloc((array->count + 1) * sizeof(*ptr));
		i = 0;
		while (i < array->count && array->ptr[i])
		{
			ptr[i] = array->ptr[i];
			++i;
		}
		ptr[i] = elem;
		free(array->ptr);
		array->ptr = ptr;
		++array->count;
	}
}

void	ft_delete_all(t_array	*array)
{
	t_ushort	i;

	i = 0;
	while (i < array->count && array->ptr[i])
	{
		ft_smart_free(&array->ptr[i]);
		++i;
	}
	free(array->ptr);
}

void	ft_initial_array(t_array	*array)
{
	array->count = 0;
	array->ptr = NULL;
}
