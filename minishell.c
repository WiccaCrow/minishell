#include "./includes/minishell.h"

int main(void)
{
	char	*command;
	char	*line;
	int		ret;

	
	write(STDIN_FILENO, GOLD, 8);
	write(STDIN_FILENO, NAME, ft_strlen(NAME));
	write(STDIN_FILENO, NONECOLOR, 5);
	ret = get_next_line(1, &line);
	while (ret != -1)
	{
		command = parser(line);
		executor(command);
		printf("Hi from main, command:\n\"%s\"\n", command);
		write(STDIN_FILENO, GOLD, 6);
		write(STDIN_FILENO, NAME, ft_strlen(NAME));
		write(STDIN_FILENO, NONECOLOR, 5);
		ret = get_next_line(1, &line);
	}
}

