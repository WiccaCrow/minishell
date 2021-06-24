#include "minishell.h"

void signal_handler(int sig)
{
	(void) sig;
	printf("\n");
	show_program_name();
}