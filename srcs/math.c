#include "so_long.h"

int	ft_pow(int basis, unsigned int exp)
{
	if (exp == 1 || basis == 0)
		return (basis);
	else if (exp == 0 || basis == 1)
		return (1);
	else
		return (basis * ft_pow(basis, exp - 1));
}

unsigned int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}
