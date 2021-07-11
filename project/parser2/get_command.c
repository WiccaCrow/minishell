#include "minishell.h"

/**
 * Функция проверяет, является ли поданная строка командой 
*/

static int	is_command(const char *word, const char *command)
{
	int	i;

	if (command)
	{
		i = 0;
		while (word[i] && command[i] && (command[i] == word[i]))
			i++;
		if (!command[i] && !word[i])
			return (1);
	}
	return (0);
}

/**
 * Функция ищет команды в строке и возвращает ее код
*/

enum e_command	get_command2(char *word)
{
	int		j;
	char	*commands[10];

	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "ctrl_c";
	commands[7] = "ctrl_d";
	commands[8] = "ctrl_slash";
	commands[9] = "exit";
	j = 0;
	while (++j <= 10)
		if (word && is_command(word, commands[j - 1]))
			return (j);
	return (0);
}
