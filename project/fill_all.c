#include "./includes/minishell.h"

/************************************
 * 		1.3. fill_all				*
 * **********************************
 * This function performs several important operations:
 * 	1) checks the validity of the data entered
 * 		by the user into the shell command line,
 * 		sets the data validity flag in the t_all
 * 		structure.
 * 				flag:		1 - data is not valid.
 * 	2) based on these data, fills in the main
 * 		structure of the program. t_all all.
*/

static int	check_end_of_input(const char *line, int flag)
{
	int i;
	
	if (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '\\' && !(flag & QUOTE))
				flag = flag | SHIELD;
			if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
				flag = flag ^ DOUBLE_QUOTE;
			if (line[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
				flag = flag ^ QUOTE;
			if (line[i] != '\\' && (flag & SHIELD) && line[i + 1])
				flag = flag & ~(SHIELD);
			i++;
		}
		return (flag);
	}
	return (0);
}

int fill_all(t_all *all)
{
	char	*line;
	int 	flag;

	line = readline(GOLD NAME NONECOLOR);
	all->line = gnl_strjoin(all->line, line);
	flag = check_end_of_input(all->line, 0);
	while (flag)
	{
		if (!(flag & SHIELD))
			all->line = gnl_strjoin(all->line, "\n");
		free(line);
		line = readline("> ");
		all->line = gnl_strjoin(all->line, line);
		flag = check_end_of_input(all->line, 0);
	}
	add_history(all->line);
	free(line);
	line = NULL;
	return (1);
}