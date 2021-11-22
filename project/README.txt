Hello!!!
Dear friend, we are very glad that you visited our project and are now
reading README.

This project is a mini-bash written in C language.
__________________________
To start use Makefile,

run ./minishell

Enjoy your use.
__________________________
Documenting the program.

In the source files, you can also find the description of the functions in the comments.
__________________________

The start of the program begins in the minishell.c file with the main ()
function.

1. main
  The start of the program begins in the minishell.c 
  file with the main () function.
Contains functions:
  1.1. sigint_handler; (in sigint_handler.c)
  1.2. sigquit_handler; (in signal_handler.c)
  1.3. main_cycle;
	1.3.1. check_line;
	1.3.2. 2dollar_handler;
	1.3.3. parser2;
	1.3.4. enter_the_pipes;
	1.3.5. executor;
  		1.3.5.1. command_not_found;
			1.3.5.1.1. 	executable;
			1.3.5.1.2. 	print_command_not_found;
				libft. ft_strlen;
  		1.3.5.2. exec_echo;
			1.3.5.2.2.1. echo_check_flag_n;
			libft. ft_strlen.
  		1.3.5.3. exec_cd;
			1.3.5.3.1. change_pwd_oldpwd;
			1.3.5.3.2. change_pwd;
 			libft. ft_strlen;
 			libft. ft_strjoin;
  		1.3.5.4. exec_pwd;
  		1.3.5.5. exec_env;
			libft.	ft_strlen;
			libft.	ft_strchr;
  		1.3.5.6. exec_export;
			1.3.5.6.1. count_env_lines;
			1.3.5.6.2. sort_env;
				1.3.5.6.2.1. do_sort_index;
				1.3.5.6.2.2. ft_strcmp_s1_less_s2;
				1.3.5.6.2.3. print_export;
					libft. ft_strlen;
 					libft. ft_strchr;
				1.3.5.6.2.4. free_sort_index;
			1.3.5.6.3. subjoin_env;
				1.3.5.6.3.1. create_new_env_array;
					1.3.5.6.3.1.1. count_lines;
						1.3.5.6.3.1.1.1. check_valid_args;
							1.3.5.6.3.1.1.1.1.1. print_not_valid;
								libft. ft_strlen;
						1.3.5.6.3.1.1.2. check_double_args;
							1.3.5.6.3.1.1.2.1. find_next_double_arg;
								libft. ft_strncmp;
							libft. ft_strchr;
 							libft. ft_strlen;
						1.3.5.6.3.1.1.3. find_env_str;
							1.3.5.6.3.1.1.3.1. get_my_env_index;
							fibft. ft_strncmp;
 							fibft. ft_strlen;
 							fibft. ft_strchr;
						fibft. ft_strncmp;
 						fibft. ft_strlen;
 					1.3.5.6.3.1.2. completion_code_malloc_error;
				1.3.5.6.3.2. export_args_to_new_env;
					1.3.5.6.3.1.1.1.1. check_valid_args;
 					1.3.5.6.3.1.1.3.3. find_env_str;
 					1.3.5.6.3.1.1.2. check_double_args;
 					1.3.5.6.3.2.1. change_env_str;
				1.3.5.6.3.3. check_arg_pwd
					libft. ft_strncmp;
 					1.3.5.3.2. change_pwd;
  		1.3.5.7. exec_unset;
			1.3.5.6.1.  count_env_lines;
 			1.3.5.6.3.1.1. count_lines;
 			1.3.5.7.1.  exec_unset_find_env_str;
				1.3.5.6.3.1.1.1. check_valid_args;
 				1.3.5.6.3.1.1.3. find_env_str;
 				1.4. ft_free;
 			1.3.5.7.2.  exec_unset_do_new_env;
  		1.5. exit_clean;
	1.3.6. free_commands;
  1.4. ft_free;
  1.5. exit_clean;
  	     wr_history;
  	1.4. ft_free;
  	1.3.6. free_commands;
  1.6. line_getter; (in line_getter.c)
  1.7. start_all; (in directory start_all)
   	1.7.1. init_env;          do copy env
		1.7.1.1. init_env_allocate_memory;
			1.3.5.6.3.1.1.3.1. get_my_env_index;
	 	1.7.1.2. init_env_err_with_exit_msh;
			1.7.1.2.1. completion_code_malloc_error;
			1.5. exit_clean;
		1.7.1.3. init_env_path;
			1.7.1.3.1. init_env_av0_path;
				libft.  ft_strlen;
 				1.7.1.2.init_env_err_with_exit_msh;
 				libft.  ft_strncmp;
 			1.7.1.3.2. init_env_path_without_path;
 				1.7.1.2. init_env_err_with_exit_msh;
 				libft.   ft_strjoin;
 			1.7.1.3.3. init_env_path_with_path;
				1.7.1.3.3.1. init_env_path_split;
					1.7.1.2. init_env_err_with_exit_msh;
 					libft.   ft_strlen;
 					libft.   ft_split;
 					libft.   ft_free;
 					libft.   ft_strncmp;
 				1.7.1.3.3.2. free_char_array;
 			1.3.5.6.3.1.1.3.1. get_my_env_index;
		1.3.5.6.3.1.1.3.1. get_my_env_index;
			libft. ft_strdup;
			libft. ft_strjoin;
 	1.7.2. init_commands;
