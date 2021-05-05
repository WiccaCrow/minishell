#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define NAME "DULCIE&GRVELVA > "
# define NONECOLOR "\x1B[0m"
# define GOLD "\033[40;33m"
# define ECHO "echo"
# define COM_NOT_FOUND ": command not found\n"

typedef struct	s_command
{
	char		**command;
}				t_command;

typedef struct	s_all {
	int			flag_executer;
	int			flag_exit;
	char		*line;
	t_command	command;
	char		**env_my;
}				t_all;


void			start_all(t_all *all, char **env);
void			init_env(t_all *all, char **env);
void			exit_clean(t_all *all, int exit_code);
int 			fill_all(t_all *all);
int				show_program_name(void);



int 			parser(t_all *all);



int 			executor(t_all *all);
int				exec_echo(t_all *all);


#endif
