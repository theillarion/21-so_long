#include "so_long.h"

static bool	ft_check_wall(const t_environment env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env.file.lines[i])
	{
		j = 0;
		while (env.file.lines[i][j])
		{
			if ((i == 0 || j == 0 || i == env.file.count - 1
					|| j == env.file.length - 1)
				&& env.file.lines[i][j] != env.map[ImageWall].key)
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

static bool	ft_check_size(const t_environment env)
{
	size_t	i;

	i = 0;
	while (env.file.lines[i])
	{
		if (ft_strlen(env.file.lines[i]) != env.file.length)
			return (false);
		++i;
	}
	if (i != env.file.count)
		return (false);
	return (true);
}

static bool	ft_calc_count_symbols(t_environment	*env)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (env->file.lines[++i] != NULL)
	{
		j = -1;
		while (env->file.lines[i][++j] != '\0')
		{
			k = -1;
			while (++k != COUNT_PAIRS)
			{
				if (env->map[k].key == env->file.lines[i][j])
				{
					++env->map[k].value;
					break ;
				}
			}
			if (k == COUNT_PAIRS)
				return (false);
		}
	}
	return (true);
}

static bool	ft_check_count_symbols(const t_environment env)
{
	if (env.map[ImageStartPosition].value != 1
		|| env.map[ImageExit].value < 1
		|| env.map[ImageCollectible].value < 1)
		return (false);
	return (true);
}

bool	ft_validation(t_environment	*env)
{
	if (!ft_check_size(*env) || !ft_check_wall(*env)
		|| !ft_calc_count_symbols(env) || !ft_check_count_symbols(*env))
		return (false);
	return (true);
}
