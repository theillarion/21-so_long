#include "so_long.h"

char	*ft_get_main_directory(u_short	size_pixels)
{
	char	*backup;
	char	*result;
	char	*number;

	number = ft_itoa(size_pixels);
	if (number == NULL)
		return (NULL);
	backup = number;
	number = ft_strjoin(number, "/");
	if (number == NULL)
		return (NULL);
	ft_smart_free((void *)&backup);
	result = ft_strjoin("images/", number);
	ft_smart_free((void *)&number);
	return (result);
}
