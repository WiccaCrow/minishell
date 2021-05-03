#include "./includes/minishell.h"

int main(void)
{
	char	*command;
	char	*line;
	int		ret;
	
	ret = get_next_line(1, &line);
	if (ret != -1)
	{
		command = parser(line);
		executor(command);
		printf("Hi from main, command:\n\"%s\"\n", command);
	}
}

