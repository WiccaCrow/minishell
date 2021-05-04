#include "../includes/minishell.h"

int executor(char *line)
{
	int i;
	
	i = printf("Hi from executor, line:\n\"%s\"\n", line);

	return (i);
}