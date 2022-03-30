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
