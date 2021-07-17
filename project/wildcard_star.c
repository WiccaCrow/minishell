#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	wildcard_open_read_dir(char *pwd, char *str_star);
void	wildcard_fill_list(char *d_name, char *str_star);
char	*wildcard_find_arg(char *d_name, char *str_star);
int		wildcard_skip_star(char *str_star, int *i_star);
int		wildcard_check_1st_midle_chars(char *d_name, char *str_star, \
			int *i_d_name, int *i_star);
char	*wildcard_check_last_chars(char *str_star, char *d_name, \
			int i_star, int i_d_name);
int		wildcard_strcmp_star_d_name(char *str_star, char *d_name, \
			int *i_d_name);
int		wildcard_strcmp_next_char(char *str_star, char *d_name, \
			int *i_d_name, char **d_name_1st_next_char);
int		wildcard_strcmp_return(int ret_strncmp, int len_star, int *i_d_name);
int		wildcard_chrcmp_d_name(char str_star, char *d_name, int *i_d_name);

static char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if ((char)c == 0)
		return (ptr);
	return (NULL);
}

int	main()
{
	// char 	pwd[] = "/Users/mdulcie/Desktop/untitled folder/";
	// char	str_star[] = "wild*s*";
	char 	pwd[] = "/Users/mdulcie";//ion
	char	str_star[] = "**ion*s";

	wildcard_open_read_dir(pwd, str_star);
	return (0);
}

/************************************************
 * 				wildcard_open_read_dir			*
 * **********************************************
*/
/* Description:
 * 			The function open current directory with opendir() and read it 
 * 		still and with readdir(). The function then uses closedir().
 * 
 * Contains functions:
 * 		wildcard_fill_list;
 * 
 * 
*/

void	wildcard_open_read_dir(char *pwd, char *str_star)
{
	DIR				*r_opndir;
	struct dirent	*r_readdir;

	r_opndir = opendir(pwd);
	if (NULL == r_opndir)
	{
		printf("opendir error.\n");
		return ;
	}
	else
	{
		r_readdir = readdir(r_opndir);
		while (r_readdir)
		{
			wildcard_fill_list(r_readdir->d_name, str_star);
			r_readdir = readdir(r_opndir);
		}
	}
	closedir(r_opndir);
}

/************************************************
 * 					wildcard_fill_list			*
 * **********************************************
*/
/* Description:
 * 			The function creates and populates the wildcard list.
 * 
 * Contains functions:
 * 		wildcard_find_arg;
 * 
 * 
*/

void	wildcard_fill_list(char *d_name, char *str_star)//если не НАЛЛ вернулся, создать листок в список
{
	char	*good;

	good = NULL;
	if ('.' != d_name[0])
		good = wildcard_find_arg(d_name, str_star);
	if (good)
		printf("\n_______\n%s\n", good);
}

/************************************************
 * 					wildcard_find_arg			*
 * **********************************************
*/
/* Description:
 * 		The function creates and populates the wildcard list.
 * 
 * Return value:
 * 		If the file name does not fit for substitution, NULL.
 * 		Otherwise, a pointer to the file name is returned.
 * Contains functions:
 * 		wildcard_skip_star;
 * 		wildcard_check_1st_midle_chars;
 * 		wildcard_check_last_chars;
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
 * 				wildcard_skip_star				*
 * **********************************************
*/
/* Description:
 * 		The function skip stars.
 * 
 * Return value:
 * 		0 if end of string after last '*'.
 * 		Else 1.
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
 * 			wildcard_check_1st_midle_chars		*
 * **********************************************
*/
/* Description:
 * 		The function check first and midle chars of string d_name.
 * 
 * Return value:
 * 		If the compared string fragment / character does not match, 
 * 		the function returns 0.
 * 		Else 1.
 * Contains functions:
 * 		wildcard_strcmp_star_d_name;
 * 		wildcard_chrcmp_d_name;
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

/************************************************
 * 			wildcard_strcmp_star_d_name			*
 * **********************************************
*/
/* Description:
 * 		The function check first and midle chars of string d_name.
 * 
 * Return value:
 * 		If the compared string fragment / character does not match, 
 * 		the function returns 0.
 * 		Else 1.
 * Contains functions:
 * 		wildcard_strcmp_star_d_name;
 * 		wildcard_chrcmp_d_name;
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
		ret_strncmp = strncmp(d_name_1st_next_char, str_star, len_star);
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
 * 			wildcard_strcmp_next_char			*
 * **********************************************
*/
/* Description:
 * 		The function sets the index i_d_name to the next required character 
 * 		*str_star.
 * 
 * Return value:
 * 		If the next required character exist - 1.
 * 		Else 0.
 * Contains functions:
 * 		ft_strchr;
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
 * 			wildcard_strcmp_return			*
 * **********************************************
*/
/* Description:
 * 		The function sets the index i_d_name to the next after compare character.
 * 
 * Return value:
 * 		If in function wildcard_strcmp_star_d_name() the compared string 
 * 		fragment / character does not match, 
 * 		the function returns 0.
 * 		Else 1.
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
 * 				wildcard_chrcmp_d_name			*
 * **********************************************
*/
/* Description:
 * 		The function compare one char.
 * 
 * Return value:
 * 		If the compared string fragment / character does not match, 
 * 		the function returns 0.
 * 		Else 1.
 * 
 * Contains functions:
 * 		ft_strchr;
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
 * 			wildcard_check_1st_midle_chars		*
 * **********************************************
*/
/* Description:
 * 		The function check last not star chars in string d_name.
 * 
 * Return value:
 * 		Pointer to a string if the entire string matched.
 * 		Else NULL.
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

// gcc -o test wildcard_star.c
