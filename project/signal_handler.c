#include "minishell.h"

void sigint_handler(int sig)
{
	(void) sig;
	g_completion_code = 1;
	g_completion_code = g_completion_code | SIGINT_CALL;
	write(STDOUT_FILENO, "\n", 1);
	show_program_name();
}

void sigquit_handler(int sig)
{
	(void) sig;
}

int free_t_line(t_line *line)
{
	if (line)
	{
		if (line->main_line)
		{
			free(line->main_line);
			line->main_line = NULL;
		}
		if (line->curr_line)
		{
			free(line->curr_line);
			line->curr_line = NULL;
		}
		if (line->tmp_line)
		{
			free(line->tmp_line);
			line->tmp_line = NULL;
		}
	}
	return (0);
}

int	sigint_switcher(t_line *line)
{
	if (g_completion_code & SIGINT_CALL)
	{
		free_t_line(line);
		g_completion_code = g_completion_code & ~(SIGINT_CALL);
		return (1);
	}
	return (0);
}

