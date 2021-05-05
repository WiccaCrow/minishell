#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define NAME "DULCIE&GRVELVA > "
# define NONECOLOR "\x1B[0m"
# define GOLD "\033[40;33m"
# define ECHO "echo"

typedef struct	s_command
{
	char		**command;
}				t_command;

int 			parser(char *line, t_command *command);



int 			executor(t_command *command);
int				exec_echo(t_command *command);


#endif
