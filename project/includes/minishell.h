#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include "./parser.h"
# include "./line_getter.h"
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define NAME "DULCIE&GRVELVA > "
# define NONECOLOR "\x1B[0m"
# define GOLD "\033[40;33m"
# define COM_NOT_FOUND ": command not found\n"
# define SYN_ERR "minishell: syntax error near unexpected token `"
# define UNEXP_EOF "bash: unexpected EOF while looking for matching " \
"`\"\'\nbash: syntax error: unexpected end of file"
# define QUOTE 1
# define DOUBLE_QUOTE 2
# define SHIELD 4
# define PIPE 1
# define SEMICOLON 2
# define START_PIPE 4
# define SIGINT_CALL (1 << 16)

#include <sys/types.h>//DIR *opendir(const char *name);
#include <dirent.h>//DIR *opendir(const char *name);

int g_completion_code; // код возврата ошибки $?

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
	int					input_fd;
	int					output_fd;
	int					redirect_type;
	int					return_code; // код возврата ошибки $?
	struct s_command	*next;
}						t_command;

typedef struct			s_all {
	char				*line;
	char 				**history; //  история комманд
	char				**env; // переменные окружения, внутрипрограммная копия
	char				*pwd;
	int					completion_code; // код возврата ошибки $?
	int					len_env_str;
	char				parse_error;
	t_command			**commands;
}						t_all;


void			start_all(t_all *all, char **env);
void			init_env(t_all *all, char **env);
void			init_commands(t_all *all);
void			exit_clean(t_all *all);
int 			fill_all(t_all *all);
void			sigint_handler(int sig);
void			sigquit_handler(int sig);

int				show_program_name(void);

int 			line_getter(t_all *all);

int				check_line(t_all *all);


int 			parser(t_all *all);
int 			parser2(t_all *all);
int				get_args(t_all *all, t_command *command, int i);
int				dollar_handler(t_all *all);
int				add_command(t_all *all, t_command *command);
enum e_command	get_command(t_all *all, int i);
enum e_command	get_command2(char *word);
int				args_list_to_arr2(t_list **args, t_command *command);
int 			set_command_to_all(t_all *all);
int 			set_start_pipes(t_all *all);
int				open_file(t_command *command, char *filename, char *pwd);
int				free_commands(t_command **commands);





int 			executor(t_all *all);
void			command_not_found(t_all *all);
void 			completion_code_malloc_error(char *array_null, char *open_name);
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
int				do_sort_index(char ***sort_env_index, int **sort, int i);
int				ft_strcmp_s1_less_s2(char *str1, char *str2);
void			print_export(t_all *all, char **sort_env_index);
void			free_sort_index(char **sort_env_index, int *sort);
void			subjoin_env(t_all *all, int i, int j);
int				count_lines(t_all *all, char *oper_name, int nb_env_lines, int j);
void			export_args_to_new_env(t_all *all, int j, char **env_new);
int				check_valid_args(t_all *all, char *oper_name, int j, int flag_print);
int				print_not_valid(t_all *all, char *args_name, char *operation_name, int flag_print);
int				check_double_args(char **args, int find_plus);
int				find_next_double_arg(char **args, int find_plus, int nb_args, int i);
int				find_env_str(t_all *all, char *oper_name, int j, char **env);
void			change_env_str(t_all *all, int j, int index, char **env);
void			create_env_str(t_all *all, int j, char **env, int *i);
void            check_arg_pwd(t_all *all);
int				exec_unset(t_all *all);
void			exec_unset_find_env_str(t_all *all, char *oper_name);
void			exec_unset_do_new_env(t_all *all, char **env_new, int nb_lines);
void			all_args_free(t_all *all);
void			exec_exit(t_all *all);
int				args_is_digit(char *args);
int				exit_code(t_all *all);
void			close_fd_output_input(t_all *all);

int			executable(t_all *all);
int	        executable_check_and_run(t_all *all, char *filename_with_path, int have_path);
int			check_command_sourse(char *com_name);
int			executable_error_print(char *com_name, char *error_message, int error_code);
int			fork_execve(t_all *all, char *com_name);
char		**path_env(t_all *all);
char		*join_directory_and_command(char *directory, char *command_name);

void	shlvl_set(t_all *all);
void	env_shlvl_null_create(t_all *all, int i);
void	env_shlvl_set_0or1(t_all *all, int index, int shlvl);
void	env_shlvl_increase_1part(t_all *all, int index);
void	env_shlvl_increase_2part(t_all *all, int index, int nb, char **env_new_shlvl);

//int         execve_pipe(t_all *all, char *filename_with_path);
int     all_pipes(t_command **commands, char **envp);
int     pipe_23(char **com_name, int fd0, char **envp, int end_flag, t_command **commands);

#endif
