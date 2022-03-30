#include "so_long.h"

int main(int argc, char	**argv)
{
	t_environment	env;

	ft_main_initial(&env);
	if (argc == 2)
	{
		errno = 0;
		if (ft_get_file(&env.file, argv[1]) == false)
			ft_fail(&env, "Error program", true);
		else
		{
			if (ft_validation(&env) == false)
				ft_fail(&env, "Error: invalid arguments", false);
			else
				ft_success(&env, "Success!");
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		//
		exit(EXIT_FAILURE);
	}
}
