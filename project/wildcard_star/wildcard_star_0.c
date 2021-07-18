#include "minishell.h"

/************************************************
 *             wildcard_open_read_dir           *
 * **********************************************
*/
/* Description:
 *         The function open current directory with opendir() and read it
 *         still and with readdir(). The function then uses closedir().
 *
 * Contains functions:
 *			wildcard_fill_list;
 *			completion_code_malloc_error;
*/

t_list	**wildcard_open_read_dir(char *pwd, char *str_star)
{
	DIR				*r_opndir;
	struct dirent	*r_readdir;
	t_list			**wc_star_list_begin;

	wc_star_list_begin = (t_list **)ft_calloc(1, sizeof(t_list *));
	r_opndir = opendir(pwd);
	if (NULL == r_opndir)
	{
		completion_code_malloc_error(NULL, "Parser, wildcard *");
		return (NULL);
	}
	else
	{
		r_readdir = readdir(r_opndir);
		while (r_readdir)
		{
			wildcard_fill_list(r_readdir->d_name, str_star, wc_star_list_begin);
			r_readdir = readdir(r_opndir);
		}
	}
	closedir(r_opndir);
	return (wc_star_list_begin);
}

/************************************************
 *                wildcard_fill_list            *
 * **********************************************
*/
/* Description:
 *             The function creates and populates the wildcard list.
 *
 * Contains functions:
 *         wildcard_find_arg;
 *
 *
*/

void	wildcard_fill_list(char *d_name, char *str_star,
			t_list **wc_star_list_begin)
{
	char	*args;

	args = NULL;
	if ('.' != d_name[0])
		args = wildcard_find_arg(d_name, str_star);
	if (args)
		ft_lstadd_back(wc_star_list_begin, ft_lstnew(ft_strdup(args)));
}

/************************************************
 *                     wildcard_find_arg            *
 * **********************************************
*/
/* Description:
 *         The function creates and populates the wildcard list.
 *
 * Return value:
 *         If the file name does not fit for substitution, NULL.
 *         Otherwise, a pointer to the file name is returned.
 * Contains functions:
 *         wildcard_skip_star;
 *         wildcard_check_1st_midle_chars;
 *         wildcard_check_last_chars;
*/

char	*wildcard_find_arg(char *d_name, char *str_star)
{
	int	i_star;
	int	i_d_name;
	int	char_in_d_name;

	i_d_name = 0;
	i_star = 0;
	char_in_d_name = 1;
	while (wildcard_skip_star(str_star, &i_star) && char_in_d_name
		&& d_name[i_d_name])
	{
		if (0 == i_star && d_name[0] != str_star[0])
			return (NULL);
		char_in_d_name = wildcard_check_1st_midle_chars(d_name,
				str_star, &i_d_name, &i_star);
	}
	if (0 == str_star[i_star] && char_in_d_name)
		return (wildcard_check_last_chars(str_star, d_name, i_star, i_d_name));
	return (NULL);
}

/************************************************
 *            wildcard_skip_star                *
 * **********************************************
*/
/* Description:
 *         The function skip stars.
 *
 * Return value:
 *         0 if end of string after last '*'.
 *         Else 1.
*/

int	wildcard_skip_star(char *str_star, int *i_star)
{
	while ('*' == str_star[*i_star])
		++(*i_star);
	if (str_star[*i_star])
		return (1);
	else
		return (0);
}

/************************************************
 *             wildcard_check_1st_midle_chars        *
 * **********************************************
*/
/* Description:
 *         The function check first and midle chars of string d_name.
 *
 * Return value:
 *         If the compared string fragment / character does not match,
 *         the function returns 0.
 *         Else 1.
 * Contains functions:
 *         wildcard_strcmp_star_d_name;
 *         wildcard_chrcmp_d_name;
 *
*/

int	wildcard_check_1st_midle_chars(char *d_name, char *str_star, int *i_d_name,
		int *i_star)
{
	int	char_in_d_name;

	if (str_star[*i_star + 1] && '*' != str_star[*i_star + 1])
	{
		char_in_d_name = wildcard_strcmp_star_d_name(&str_star[*i_star],
				d_name, i_d_name);
		while (str_star[*i_star] && str_star[*i_star] != '*')
			++(*i_star);
	}
	else
	{
		char_in_d_name = wildcard_chrcmp_d_name(str_star[*i_star],
				&d_name[*i_d_name], i_d_name);
		++(*i_star);
	}
	return (char_in_d_name);
}
