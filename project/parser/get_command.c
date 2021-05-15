#include "../includes/minishell.h"

char	*get_command_name(const char *str, int i)
{
	int		flag;
	char	*command_name;
	
	command_name = NULL;
	while (str[i])
	{
		if (str[i] == '\\' && !(flag & QUOTE))
		{
			flag = flag & SHIELD;
			i++;
		}
		if (str[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
		{
			flag = flag ^ DOUBLE_QUOTE;
			i++;
		}
		if (str[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
		{
			flag = flag ^ QUOTE;
			i++;
		}
		if (str[i] && ((str[i] != ' ' && str[i] != ';' && str[i] != '|')
						|| flag))
			command_name = add_chr(command_name, str[i]);
		else
			return (command_name);
		i++;
		if (str[i])
			flag = flag & ~(SHIELD);
	}
	return (command_name);
}

static int	is_command(const char *str, const char *command, int i)
{
	char *command_name;
	int k;
	int j;
	
	command_name = get_command_name(str, i);
	if (command_name && command)
	{
		k = 0;
		j = i;
		while (command_name[j] == command[k] && (command_name[j] && 
		command[k++]))
			j++;
		if (command_name[j] == 0 && !command[k])
			return (1);
	}
	return (0);
}


enum e_command	get_command(t_all *all, int i)
{
	int	j;

	j = 0;
	while (++j <= 10)
		if (all->line && is_command(all->line, all->all_commands[j - 1], i))
			return j;
	return (0);
}