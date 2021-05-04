#include "../includes/minishell.h"

char *parser(char *line)
{
	printf("Hi from parser, line:\n\"%s\"\n", line);
	return (line);
}