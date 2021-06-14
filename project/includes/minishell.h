#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include "./parser.h"
# include "./line_getter.h"
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define NAME "DULCIE&GRVELVA > "
# define NONECOLOR "\x1B[0m"
# define GOLD "\033[40;33m"
# define COM_NOT_FOUND ": command not found\n"
# define QUOTE 1
# define DOUBLE_QUOTE 2
# define SHIELD 4
# define PIPE 1
# define SEMICOLON 2

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
	exit_shell,
	other,
	start
};

typedef struct			s_command {
	enum e_command		flag_command;
	char 				**args; // аргументы комманды
	int					end_flag;
	int					input_fd;
	int					output_fd;
	int					redirect_type;
	int					return_code; // код возврата ошибки $?
	struct s_command	*next;
}						t_command;

typedef struct			s_all {
	enum e_command		flag_command;
	char				*line;
	char 				**args; // аргументы комманды
	char 				**history; //  история комманд
	char				**env; // переменные окружения, внутрипрограммная копия
	char				*all_commands[10];
	char				*pwd;
	int					completion_code; // код возврата ошибки $? return заменила на completion
	int					pipe_on_of; // exit срабатывает только если нет '|'
	int					len_env_str;
	int					parse_error;
	t_command			**commands;
}						t_all;


void			start_all(t_all *all, char **env);
void			init_env(t_all *all, char **env);
void			init_commands(t_all *all);
void			exit_clean(t_all *all, int code);
int 			fill_all(t_all *all);
int				show_program_name(void);

int 			line_getter(t_all *all);

int 			parser(t_all *all);
int 			parser2(t_all *all);
int				get_args(t_all *all, t_command *command, int i);
int				dollar_handler(t_all *all);
int				add_command(t_all *all, t_command *command);
enum e_command	get_command(t_all *all, int i);
enum e_command	get_command2(char *word);
int				args_list_to_arr2(t_list **args, t_command *command);
int 			set_command_to_all(t_all *all);
int				open_file(t_command *command, char *filename);




int 			executor(t_all *all);
void			command_not_found(t_all *all);
void 			completion_code_malloc_error(int	*code_to_on, char *array_null, char *open_name);
int				exec_echo(t_all *all);
int				exec_cd(t_all *all);
int				get_my_env_index(char **my_env, char *env_str, size_t len_env_str);
void			change_oldpwd(t_all *all);
void			change_pwd(t_all *all);
int				get_my_env_index(char **my_env, char *env_str, size_t len_env_str);
void			exec_pwd(t_all *all);
void			exec_env(t_all *all);
int				exec_export(t_all *all);
int				count_env_lines(t_all *all);
void			sort_env(t_all *all, int i, int k, int j);
int				do_sort_index(t_all *all, char ***sort_env_index, int **sort, int i);
int				ft_strcmp_s1_less_s2(char *str1, char *str2);
void			print_export(char **sort_env_index);
void			free_sort_index(char **sort_env_index, int *sort);
void			subjoin_env(t_all *all, int i, int j);
int				count_lines(t_all *all, char *oper_name, int nb_env_lines, int j);
void			export_args_to_new_env(t_all *all, int j, char **env_new, int *i);
int				check_valid_args(t_all *all, char *oper_name, int j, int flag_print);
int				print_not_valid(t_all *all, char *args_name, char *operation_name, int flag_print);
int				check_double_args(char **args, int find_plus);
int				find_next_double_arg(char **args, int find_plus, int nb_args, int i);
int				find_env_str(t_all *all, char *oper_name, int j);
void			change_env_str(t_all *all, int j, int index);
int				exec_unset(t_all *all);
void			exec_unset_find_env_str(t_all *all, char *oper_name);
void			exec_unset_do_new_env(t_all *all, char **env_new, int nb_lines);
void			all_args_free(t_all *all);
void			exec_exit(t_all *all);
int				exit_code(t_all *all);

int			executable(t_all *all);
int			check_command_sourse(t_all *all, char *com_name);
int			path_to_executable(t_all *all);
int	executable_error_print(int	*code_to_on, char *com_name, char *error_message, int error_code);
char		*command_name(char *string, char stop_copy);
int			find_file(t_all *all, char *com_name);
int			fork_execve(t_all *all, char *com_name);
char		**path_env(t_all *all);
int			find_file_in_dir(t_all *all, char *directory, char *command_name, char *tmp_com_name);
char		*join_directory_and_command(char *directory, char *command_name);

#endif
