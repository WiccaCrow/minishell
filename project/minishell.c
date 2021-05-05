#include "./includes/minishell.h"

int show_program_name()
{
	write(STDOUT_FILENO, GOLD, 8);
	write(STDOUT_FILENO, NAME, ft_strlen(NAME));
	write(STDOUT_FILENO, NONECOLOR, 5);
	return (0);
}

int main(void)
{
	t_command	command;
	char		*line;
	int			ret;

	show_program_name();
	ret = get_next_line(1, &line);
	while (ret != -1)
	{
		parser(line, &command);
		executor(&command);
		show_program_name();
		ret = get_next_line(1, &line);
	}
}
