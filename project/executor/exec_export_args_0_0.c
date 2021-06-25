#include "../includes/minishell.h"

/************************************
 * 				exec_export			*
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
 * 		count_env_lines;
 * 		sort_env;
 * 		subjoin_env;
*/

int	exec_export(t_all *all)
{
	int	i;

    g_completion_code = 0;
	i = count_env_lines(all);
	if (!all->args[0])
		sort_env(all, i, -1, 0);
	else
		subjoin_env(all, i, -1);
	return (0);
}

/************************************
 * 			count_env_lines			*
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
 * 				sort_env			*
 * **********************************
*/
/* Description:
 * 		Sort env array for export.
 * Contains functions:
 * 	do_sort_index;
 * 	ft_strcmp_s1_less_s2;
 * 	print_export;
 * 	free_sort_index;
*/

void	sort_env(t_all *all, int i, int k, int j)
{
	int		j_zero;
	char	**sort_env_index;
	int		*sort;

    g_completion_code = do_sort_index(&sort_env_index, &sort, i);
	if (g_completion_code)
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
	print_export(all, sort_env_index);
	free_sort_index(sort_env_index, sort);
}

/************************************
 * 			do_sort_index			*
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

/************************************
 * 		ft_strcmp_s1_less_s2		*
 * **********************************
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
