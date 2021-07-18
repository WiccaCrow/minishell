#include "minishell.h"

/************************************************
 *        wildcard_strcmp_star_d_name           *
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

int	wildcard_strcmp_star_d_name(char *str_star, char *d_name, int *i_d_name)
{
	int		len_star;
	int		ret_strncmp;
	char	*d_name_1st_next_char;

	len_star = 0;
	while (str_star[len_star] && str_star[len_star] != '*')
		++len_star;
	if (!wildcard_strcmp_next_char(str_star, d_name, i_d_name,
			&d_name_1st_next_char))
		return (0);
	ret_strncmp = 1;
	while (d_name[*i_d_name] && ret_strncmp)
	{
		ret_strncmp = ft_strncmp(d_name_1st_next_char, str_star, len_star);
		if (!ret_strncmp)
			break ;
		++(*i_d_name);
		if (!wildcard_strcmp_next_char(str_star, d_name, i_d_name,
				&d_name_1st_next_char))
			return (0);
	}
	return (wildcard_strcmp_return(ret_strncmp, len_star, i_d_name));
}

/************************************************
 *           wildcard_strcmp_next_char          *
 * **********************************************
*/
/* Description:
 *         The function sets the index i_d_name to the next required character
 *         *str_star.
 *
 * Return value:
 *         If the next required character exist - 1.
 *         Else 0.
 * Contains functions:
 *         ft_strchr;
*/

int	wildcard_strcmp_next_char(char *str_star, char *d_name, int *i_d_name,
		char **d_name_1st_next_char)
{
	if (!d_name[*i_d_name])
		return (0);
	*d_name_1st_next_char = ft_strchr(&d_name[*i_d_name], *str_star);
	if (NULL == *d_name_1st_next_char)
		return (0);
	*i_d_name = *d_name_1st_next_char - d_name;
	return (1);
}

/************************************************
 *             wildcard_strcmp_return           *
 * **********************************************
*/
/* Description:
 *      The function sets the index i_d_name to the next after 
 * 		compare character.
 *
 * Return value:
 *         If in function wildcard_strcmp_star_d_name() the compared string
 *         fragment / character does not match,
 *         the function returns 0.
 *         Else 1.
*/

int	wildcard_strcmp_return(int ret_strncmp, int len_star, int *i_d_name)
{
	if (0 == ret_strncmp)
	{
		while (--len_star)
			++(*i_d_name);
		return (1);
	}
	else
		return (0);
}

/************************************************
 *              wildcard_chrcmp_d_name          *
 * **********************************************
*/
/* Description:
 *         The function compare one char.
 *
 * Return value:
 *         If the compared string fragment / character does not match,
 *         the function returns 0.
 *         Else 1.
 *
 * Contains functions:
 *         ft_strchr;
*/

int	wildcard_chrcmp_d_name(char str_star_char, char *d_name, int *i_d_name)
{
	char	*d_name_char;
	int		ret_strchr;

	d_name_char = ft_strchr(d_name, str_star_char);
	if (NULL == d_name_char)
		return (0);
	ret_strchr = d_name_char - d_name;
	*i_d_name += ret_strchr;
	return (1);
}

/************************************************
 *             wildcard_check_1st_midle_chars        *
 * **********************************************
*/
/* Description:
 *         The function check last not star chars in string d_name.
 *
 * Return value:
 *         Pointer to a string if the entire string matched.
 *         Else NULL.
*/

char	*wildcard_check_last_chars(char *str_star, char *d_name, int i_star,
			int i_d_name)
{
	if ('*' != str_star[i_star - 1] && d_name[i_d_name])
	{
		while (d_name[i_d_name])
			++i_d_name;
		while ('*' != str_star[i_star])
		{
			--i_star;
			--i_d_name;
			if ('*' != str_star[i_star] && str_star[i_star] != d_name[i_d_name])
				return (NULL);
		}
	}
	return (d_name);
}
