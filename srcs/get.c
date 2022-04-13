#include "so_long.h"

char	*ft_get_main_directory(t_ushort	size_pixels)
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

int	ft_get_number_with_count(int number, int count)
{
	if (count == 0 || number > 9 || number < -9)
		return (0);
	if (count == 1)
		return (number);
	else
		return (number * pow(10, count - 1)
			+ ft_get_number_with_count(number, count - 1));
}
