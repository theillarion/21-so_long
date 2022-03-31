#include "so_long.h"


/*void	ft_output_2(const t_array	*arr)
{
	size_t	i;

	printf("Size character: %d\n", arr->count);
	i = 0;
	if (arr->ptr == NULL)
	{
		printf("NULL\n");
		return ;
	}
	while (i < arr->count && arr->ptr[i])
	{
		printf("Elem %%%ld: %s (%p)\n", i, (char *)arr->ptr[i], arr->ptr[i]);
		++i;
	}
}
*/

void	ft_push_back(t_array	*array, const void	*elem)
{
	void			**ptr;
	u_short	i;

	if (array != NULL && elem != NULL)
	{
		ptr = (void **)malloc((array->count + 1) * sizeof(*ptr));
		i = 0;
		while (i < array->count && array->ptr[i])
		{
			ptr[i] = (void *)malloc((ft_strlen((char *)array->ptr[i]) + 1) * sizeof(**array->ptr));
			ft_memcpy(ptr[i], array->ptr[i], (ft_strlen((char *)array->ptr[i])+ 1) * sizeof(**array->ptr));
			free(array->ptr[i++]);
		}
		ptr[i] = (void *)malloc((ft_strlen((char *)elem)+ 1) * sizeof(*elem));
		ft_memcpy(ptr[i], elem, (ft_strlen((char *)elem)+ 1) * sizeof(*elem));
		free(array->ptr);
		array->ptr = ptr;
		++array->count;
	}
}

void	ft_push_adrs(t_array	*array, void	*elem)
{
	void			**ptr;
	u_short	i;

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
	u_short	i;

	i = 0;
	while (i < array->count && array->ptr[i])
	{
		ft_smart_free(&array->ptr[i]);
		++i;
	}
	free(array->ptr);
}
