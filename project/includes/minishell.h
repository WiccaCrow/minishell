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

typedef struct			s_command {
	enum e_command		flag_command;
	char 				**args; // аргументы комманды
	int					end_flag;
	int					return_code; // код возврата ошибки $?
	struct s_command	*next;
}						t_command;

typedef struct			s_all {
	enum e_command		flag_command;
	char				*line;
	char 				**args; // аргументы комманды
	char				**env; // переменные окружения, внутрипрограммная копия
	char				*all_commands[10];
	char				*pwd;
    char    			*oldpwd;
	int					return_code; // код возврата ошибки $?
	t_command			**commands;
}						t_all;


void			start_all(t_all *all, char **env);
void			init_env(t_all *all, char **env);
void			init_commands(t_all *all);
void			exit_clean(t_all *all);
int 			fill_all(t_all *all);
int				show_program_name(void);



int 			parser(t_all *all);
int 			get_args(t_all *all);
int				dollar_handler(t_all *all);
int				add_command(t_all *all);



int 			executor(t_all *all);
int				exec_echo(t_all *all);
int				exec_cd(t_all *all);
void			exec_pwd(t_all *all);
void			exec_env(t_all *all, char **env_my);////////////
int				exec_export(t_all *all);
void	sort_env(t_all *all, int i, int k, int j);
int	do_sort_index(char ***sort_env_index, int **sort, int i);
void			all_args_free(t_all *all);
void	subjoin_env(t_all *all, int i, int j);


#endif
