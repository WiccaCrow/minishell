#include "minishell.h"

/************************************
 * 	1.3.5.6.	exec_export			*
 * **********************************
*/
/* Description:
 * 		If no arguments, print sort env array.
 * 		The shell shall give the export attribute 
 * 		to the variables corresponding to the 
 * 		specified names, which shall cause them 
 * 		to be in the environment of subsequently 
 * 		executed commands. If the name of a variable 
 * 		is followed by = word, then the value of 
 * 		that variable shall be set to word.
 * 
 * Contains functions:
 * 	1.3.5.6.1.	count_env_lines;
 * 	1.3.5.6.2.	sort_env;
 * 	1.3.5.6.3.	subjoin_env;
*/

int	exec_export(t_all *all, t_command *tmp)
{
	int	i;

	g_completion_code = 0;
	i = count_env_lines(all);
	if (!tmp->args[0])
		sort_env(all, tmp, i, 0);
	else
		subjoin_env(all, tmp, i);
	return (0);
}

/************************************
 * 	1.3.5.6.1. count_env_lines		*
 * **********************************
*/
/* Description:
 * 		Counts the number of lines in
 * 		env array.
*/

int	count_env_lines(t_all *all)
{
	int	i;

	i = 0;
	while (all->env[i])
		++i;
	return (i);
}

/************************************
 * 	1.3.5.6.2.	sort_env			*
 * **********************************
*/
/* Description:
 * 		Sort env array for export.
 * Contains functions:
 * 	1.3.5.6.2.1. do_sort_index;
 * 	1.3.5.6.2.2. ft_strcmp_s1_less_s2;
 * 	1.3.5.6.2.3. print_export;
 * 	1.3.5.6.2.4. free_sort_index;
*/

void	sort_env(t_all *all, t_command *tmp, int i, int j)
{
	int		j_zero;
	char	**sort_env_index;
	int		*sort;
	int		k;

	if (0 == i || do_sort_index(&sort_env_index, &sort, i))
		return ;
	j_zero = 0;
	while (i)
	{
		k = -1;
		j = 0;
		while (!sort[j_zero] && all->env[j_zero])
			++j_zero;
		j += j_zero;
		while (all->env[++k])
			if (ft_strcmp_s1_less_s2(all->env[j], all->env[k]) && sort[k])
				j = k;
		sort_env_index[--i] = all->env[j];
		sort[j] = 0;
	}
	print_export(tmp, sort_env_index);
	free_sort_index(sort_env_index, sort);
}

/************************************
 *     1.3.5.6.2.1. do_sort_index   *
 * **********************************
*/
/* Description:
 * 		Do array for sort index.
 * 		The Sort array contains ascending indices of strings.
*/

int	do_sort_index(char ***sort_env_index, int **sort, int i)
{
	int	k;

	k = -1;
	*sort_env_index = (char **)malloc((i + 1) * sizeof(char *));
	(*sort_env_index)[i] = NULL;
	*sort = (int *)malloc((i + 1) * sizeof(int));
	(*sort)[i] = 0;
	while (++k < i)
		(*sort)[k] = 1;
	if (*sort_env_index == NULL || *sort == NULL)
		completion_code_malloc_error(NULL, "export without arguments: ");
	return (g_completion_code);
}

/**************************************
 *  1.3.5.6.2.2. ft_strcmp_s1_less_s2 *
 * ************************************
*/
/* Description:
 * 		Compare two strings.
 * Return value:
 * 		if str1 less str2 return 1,
 * 		else return 0.
*/

int	ft_strcmp_s1_less_s2(char *str1, char *str2)
{
	while (*str1 == *str2 && *str2 && *str1)
	{
		++str1;
		++str2;
	}
	if (*str1 < *str2)
		return (1);
	return (0);
}
