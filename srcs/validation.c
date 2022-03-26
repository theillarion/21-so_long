#include "so_long.h"

bool	ft_check_wall(const t_environment env)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (env.file.lines[i])
	{
		while (env.file.lines[i][j])
		{
			if ((i == 0 || j == 0) && env.file.lines[i][j] != env.map[WALL].key)
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

bool	ft_check_size(const t_environment env)
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

bool	ft_calc_count_symbols(t_environment	*env)
{
	size_t	i;
	size_t	j;
	//size_t	k;

	i = 0;
	while (env->file.lines[i] != NULL)
	{
		j = 0;
		while (env->file.lines[i][j] != '\0')
		{
			/*k = 0;
			while (k != COUNT_PAIRS)
			{
				if (env->map[k].key == env->file.lines[i][j])
					break ;
				++k;
			}
			*/
			if (env->file.lines[i][j] == '0')
				++env->map[EMPTY_SPACE].value;
			else if (env->file.lines[i][j] == '1')
				++env->map[WALL].value;
			else if (env->file.lines[i][j] == 'C')
				++env->map[COLLECTIBLE].value;
			else if (env->file.lines[i][j] == 'E')
				++env->map[EXIT].value;
			else if (env->file.lines[i][j] == 'P')
				++env->map[START_POSITION].value;
			else
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

bool	ft_check_count_symbols(const t_environment env)
{
	if (env.map[START_POSITION].value != 1
		|| env.map[EXIT].value < 1 || env.map[COLLECTIBLE].value < 1)
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
