#include "../includes/minishell.h"//"minishell.h"

/************************************
 * 		env_shlvl_increase_1part	*
 * 		env_shlvl_increase_2part	*
 * **********************************
*/
/* Description:
 * 		The function converts the value of the SHLVL 
 * 		variable to a number and, depending on the 
 * 		received value, does the following:
 * 		1) if the number is less than 1000, at the 
 * 			exit from the function, the line of the 
 * 			env-array of SHLVL will be increased by 1.
 * 		2) if the number is 1000, at the exit from the 
 * 			function, the line of the ENV array of 
 * 			SHLVL will be "SHLVL=".
 * 		3) if the number is greater than 1000, at the 
 * 			exit from the function, the line of the 
 * 			ENV array of SHLVL will be "SHLVL=1". And 
 * 			a warning will also be issued:
 * 			"minishell: warning: shell level (nb) too 
 * 			high, resetting to 1", where nb is this 
 * 			number.
 * Contains functions:
 * 		libft. ft_atoi;
 * 		libft. ft_itoa;
 * 		libft. ft_strdup;
 * 		libft. ft_putnbr_fd;
 * 		
*/

void	env_shlvl_increase_1part(t_all *all, int index)
{
	int		nb;
	char	*env_new_shlvl;
	char	*str_nb;

	nb = ft_atoi(&(all->env[index][6]));
	++nb;
	if (nb < 1000)
	{
		env_new_shlvl = NULL;
		str_nb = ft_itoa(nb);
		if (str_nb)
		{
			env_new_shlvl = ft_strjoin("SHLVL=", str_nb);
			free(str_nb);
			str_nb = NULL;
		}
	}
	env_shlvl_increase_2part(all, index, nb, &env_new_shlvl);
}

void	env_shlvl_increase_2part(t_all *all, int index, int nb, char **env_new_shlvl)
{
	if (nb == 1000)
		*env_new_shlvl = ft_strdup("SHLVL=");
	if (nb > 1000)
	{
		write(STDERR_FILENO, "minishell: warning: shell level (", 34);
		ft_putnbr_fd(nb, STDERR_FILENO);
		write(STDERR_FILENO, ") too high, resetting to 1\n", 28);
		*env_new_shlvl = ft_strdup("SHLVL=1");
	}
	if (*env_new_shlvl)
	{
		free(all->env[index]);
		all->env[index] = *env_new_shlvl;
	}
	else
		write(STDERR_FILENO, "Executable SHLVL: malloc error. Don't create new SHLVL\n", 56);
}

/************************************
 * 			 env_shlvl_set_0or1		*
 * **********************************
*/
/* Description:
 * 		The function sets the value of the SHLVL 
 * 		env-variable to 1 or 0 in accordance with 
 * 		the value of the shlvl flag.
 * Contains functions:
 * 		libft. ft_strdup;
*/

void	env_shlvl_set_0or1(t_all *all, int index, int shlvl)
{
	char	*shlvl_new;

	if (shlvl == 1)
		shlvl_new = ft_strdup("SHLVL=1");
	else
		shlvl_new = ft_strdup("SHLVL=0");
	if (shlvl_new == NULL)
	{
		write(STDERR_FILENO, "Executable SHLVL: malloc error. Don't create new SHLVL\n", 56);
		return ;
	}
	free(all->env[index]);
	all->env[index] = shlvl_new;
}

/************************************
 * 		 env_shlvl_null_create		*
 * **********************************
*/
/* Description:
 * 		If at the moment of calling the function 
 * 		(that is, before starting the minishell 
 * 		program) the variable SHLVL was absent in 
 * 		the passed env-array, the function creates 
 * 		this variable and sets it to 1 (SHLVL=1).
 * Contains functions:
 * 		libft. ft_strdup;
*/

void	env_shlvl_null_create(t_all *all, int i)
{
	char	**env_new;

	env_new = (char **)malloc((i + 1) * sizeof(char *));
	if (env_new)
	{
		env_new[i--] = NULL;
		env_new[i] = ft_strdup("SHLVL=1");
		if (env_new[i] == NULL)
		{
			write(STDERR_FILENO, "Executable SHLVL: malloc error. Don't create new SHLVL\n", 56);
			free(env_new);
		}
		else
		{
			while (--i >= 0)
				env_new[i] = all->env[i];
			free(all->env);
			all->env = env_new;
		}
	}
	else
		write(STDERR_FILENO, "Executable SHLVL: malloc error. Don't create new SHLVL\n", 56);
}

/************************************
 * 			 shlvl_increase			*
 * **********************************
*/
/* Description:
 * 		The function searches for the string with SHLVL
 * 		variable in the env-array. If no string is found,
 * 		a new string with the value "SHLVL=1" is created 
 * 		in the env-array (function: env_shlvl_null_create).
 * Contains functions:
 * 		get_my_env_index;
 * 		count_env_lines;
 * 		env_shlvl_null_create;
 * 		env_shlvl_set_0or1;
 * 		args_is_digit;
 * 		env_shlvl_increase_1part;
*/

void	shlvl_set(t_all *all)
{
		int		index;
		int		i;

		index = get_my_env_index(all->env, "SHLVL", 5);
		if (all->env[index] == NULL)
		{
			i = count_env_lines(all) + 1;
			env_shlvl_null_create(all, i);
		}
		else
		{
			if (all->env[index][6] == '\0')
				env_shlvl_set_0or1(all, index, 1);
			else if (all->env[index][6] != '+')
			{
				if (!args_is_digit(&(all->env[index][6])))
				{
					if (all->env[index][6] == '-' && !(all->env[index][6] == '-' && all->env[index][7] == '0' && all->env[index][8] == '\0'))
						env_shlvl_set_0or1(all, index, 0);
					else
						env_shlvl_increase_1part(all, index);
				}
				else
					env_shlvl_set_0or1(all, index, 1);
			}
		}
}