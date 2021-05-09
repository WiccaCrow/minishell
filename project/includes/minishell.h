#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include "./parser.h"
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define NAME "DULCIE&GRVELVA > "
# define NONECOLOR "\x1B[0m"
# define GOLD "\033[40;33m"
# define COM_NOT_FOUND ": command not found\n"
# define QUOTE 1
# define DOUBLE_QUOTE 2
# define SHIELD 4

enum e_command
{
	not_found,
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	ctrl_c,
	ctrl_d,
	ctrl_slash,
	exit_shell
};

typedef struct		s_all {
	enum e_command	flag_command;
	char			*line;
	char 			**args; // аргументы комманды
	char			**env; // переменные окружения, внутрипрограммная копия
	char			*all_commands[10];
	char			*pwd;
	int				return_code; // код возврата ошибки $?
}					t_all;


void			start_all(t_all *all, char **env);
void			init_env(t_all *all, char **env);
void			init_commands(t_all *all);
void			exit_clean(t_all *all);
int 			fill_all(t_all *all);
int				show_program_name(void);



int 			parser(t_all *all);
int 			get_args(t_all *all);
int				dollar_handler(char **line, t_all *all);



int 			executor(t_all *all);
int				exec_echo(t_all *all);
int				exec_cd(t_all *all);
void			exec_pwd(t_all *all);
void			exec_env(t_all *all);
void			all_args_free(t_all *all);


#endif
