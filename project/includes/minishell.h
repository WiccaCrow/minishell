#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "parser.h"
# include "line_getter.h"
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define NAME "DULCIE&GRVELVA > "
# define NONECOLOR "\x1B[0m"
# define CURSIVE "\x1B[3;36m"
# define GOLD "\033[40;33m"
# define COM_NOT_FOUND ": command not found\n"
# define SYN_ERR "minishell: syntax error near unexpected token `"
# define UNEXP_EOF "bash: unexpected EOF while looking for matching `\"\'\n"
# define UNEXP_EOF2 "bash: syntax error: unexpected end of file"
# define QUOTE 1
# define DOUBLE_QUOTE 2
# define SHIELD 4
# define PIPE 1
# define SEMICOLON 2
# define START_PIPE 4
# define SIGINT_CALL 0x10000

extern int	g_completion_code; // код возврата ошибки $?

enum	e_command
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

typedef struct s_command {
	enum e_command		flag_command;
	char				**args;
	int					end_flag;
	int					input_fd;
	int					output_fd;
	int					redirect_type;
	struct s_command	*next;
}						t_command;

typedef struct s_all {
	char				*line;
	char				**history;
	char				**env;
	char				*pwd;
	int					len_env_str;
	int					nb_arg;
	char				parse_error;
	t_command			**commands;
	int					fd0;
	int					check_line;
	pid_t				waitpid;
}						t_all;

int				show_commands(t_command **commands);

void			start_all(t_all *all, char **env, char *av0);
void			init_env(t_all *all, char **env, char *av0);
int				init_env_allocate_memory(t_all *all, char **env);
void			init_env_err_with_exit_msh(t_all *all, char *array_null, \
					char *oper_name);
void			init_env_path(t_all *all, char *av0, int i);
void			init_env_av0_path(t_all *all, char *av0, char **av0_path);
void			init_env_path_without_path(t_all *all, char *av0_path, int i);
void			init_env_path_with_path(t_all *all, char *av0_path, \
					int index_path, int j);
void			exit_clean(t_all *all);
void			sigint_handler(int sig);
void			sigquit_handler(int sig);
int				show_program_name(void);

int				fill_all(t_all *all);
int				line_getter(t_all *all);
int				check_line(t_all *all);
int				get_next_word_lc(char *line, int i, char **tmp_line);
int				parser2(t_all *all);
int				heredoc_handle(t_all *all, int i);
int				do_heredoc_redirects(t_list **args);

int				dollar_handler(t_all *all);
int				add_command(t_all *all, t_command *command);
enum e_command	get_command(char *word);
int				args_list_to_arr2(t_list **args, t_command *command);
int				set_start_pipes(t_all *all);
int				open_file(t_command *command, char *filename, char *pwd);
int				free_commands(t_command **commands);

int				executor(t_all *all, t_command *tmp);
void			command_not_found(t_all *all, t_command *tmp);
void			print_command_not_found(t_command *tmp);
void			completion_code_malloc_error(char *array_null, char *open_name);
void			completion_code_int_ret_error(char *oper_name, int error_code);
int				completion_code_fork_error(char *oper_name, char *err_text, \
					int error_code);
int				exec_echo(t_command *tmp);
void			echo_check_flag_n(t_command *tmp, int *i, int *flag_n);
int				exec_cd(t_all *all, t_command *tmp);
int				get_my_env_index(char **my_env, char *env_str, \
					size_t len_env_str);
void			change_oldpwd(t_all *all);
void			change_pwd(t_all *all);
void			exec_pwd(t_all *all, t_command *tmp);
void			exec_env(t_all *all, t_command *tmp);
int				exec_export(t_all *all, t_command *tmp);
int				count_env_lines(t_all *all);
void			sort_env(t_all *all, t_command *tmp, int i, int j);
int				do_sort_index(char ***sort_env_index, int **sort, int i);
int				ft_strcmp_s1_less_s2(char *str1, char *str2);
void			print_export(t_command *tmp, char **sort_env_index);
void			free_sort_index(char **sort_env_index, int *sort);
void			subjoin_env(t_all *all, t_command *tmp, int i);
char			**create_new_env_array(t_all *all, t_command *tmp, int i);
int				count_lines(t_all *all, t_command *tmp, char *oper_name, \
					int nb_env_lines);
int				export_args_to_new_env(t_all *all, t_command *tmp, \
					char **env_new);
int				check_valid_args(char *argj, char *oper_name, int flag_print);
int				print_not_valid(char *args_name, char *operation_name, \
					int flag_print);
int				check_double_args(char **args, int find_plus);
int				find_next_double_arg(char **args, int find_plus, int nb_args, \
					int i);
int				find_env_str(t_all *all, t_command *tmp, char *oper_name, \
					char **env);
int				change_env_str(t_all *all, t_command *tmp, int index, \
					char **env);
int				create_env_str(t_all *all, t_command *tmp, char **env, int *i);
void			check_arg_pwd(t_all *all);
int				exec_unset(t_all *all, t_command *tmp);
void			exec_unset_find_env_str(t_all *all, t_command *tmp, \
					char *oper_name);
void			exec_unset_do_new_env(t_all *all, char **env_new, int nb_lines);
void			exec_exit(t_all *all, t_command *tmp);
int				args_is_digit(char *args);
int				exit_code(t_all *all, t_command *tmp);
void			close_fd_output_input(t_command *tmp);

int				executable(t_all *all, t_command *tmp);
int				executable_check_and_run(t_all *all, char *name_path, \
					int have_path, t_command *tmp);
int				check_command_sourse(char *com_name);
int				executable_error_print(char *com_name, char *error_message, \
					int error_code);
void			repointer_to_filename_with_path(char **args0, \
					char *filename_with_path);
int				fork_execve(t_all *all, t_command *tmp, char *com_name);
char			**path_env(t_all *all);
char			*join_directory_and_command(char *directory, \
					char *command_name);

void			shlvl_set(t_all *all, int index, int i);
void			env_shlvl_null_create(t_all *all, int i);
void			env_shlvl_set_0or1(t_all *all, int index, int shlvl);
void			env_shlvl_increase_1part(t_all *all, int index);
void			env_shlvl_increase_2part(t_all *all, int index, int nb, \
					char **env_new_shlvl);

void			enter_the_pipes(t_all *all, t_command *tmp);
pid_t			*nb_pipes(t_command *tmp, pid_t **pid);
int				do_pipes(t_all *all, t_command *tmp, pid_t *pid);
int				pipe_1st_midle(t_all *all, t_command *tmp);
void			dupfd_in_pipe_1st_midle(t_all *all, t_command *tmp, \
					int *file_pipes);
void			exec_command_with_pipe(t_all *all, t_command *tmp);
int				pipe_last(t_all *all, t_command *tmp);
int				pipe_fork_if_error(t_all *all);
void			wait_status_fork(pid_t onepid);

void			ft_free(void **pointer);

#endif
