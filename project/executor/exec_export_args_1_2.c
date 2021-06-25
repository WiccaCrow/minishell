#include "../includes/minishell.h"

/************************************
 * 			check_arg_pwd			*
 * **********************************
*/
/* Description:
 * 		The function searches the (*all->commands)->args for a string
 * 		containing the PWD key. If all the keys found
 * 		without assigning or changing the values of the
 * 		PWD variable (without '=', without "+="), search
 * 		for the PWD variable in the my env-array, if
 * 		there is no symbol after the key '=' (end of line),
 * 		the PWD variable is assigned the value of the current
 * 		directory from all-pwd.
 *
 * Contains functions:
 * 		1. ft_strncmp;
 * 		2. change_pwd;
*/

void    check_arg_pwd(t_all *all)
{
    int i;
    int cmp;

    i = 0;
    while ((*all->commands)->args[++i])
    {
        cmp = ft_strncmp((*all->commands)->args[i], "PWD", 3);
        if (!cmp && ((*all->commands)->args[i][3] == '=' || ((*all->commands)->args[i][3] == '+' && (*all->commands)->args[i][4] == '=')))
            break;
    }
    if ((*all->commands)->args[i] == NULL)
        i = get_my_env_index(all->env, "PWD", 3);
    if (all->env[i] && all->env[i][3] == '\0')
        change_pwd(all);
}