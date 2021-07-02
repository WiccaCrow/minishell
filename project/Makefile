NAME		=	minishell
LIBFT		=	libft.a
CCF			=	clang $(CFLAGS)
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g -I./includes/
LG_PATH		=	line_getter/
LG_SRCS		=	line_getter.c line_utils.c history_handler.c term_switch.c key_handlers.c \
				rdwr_history.c
LC_PATH		=	line_checker/
LC_SRCS		=	line_checker.c
PARSER2_PATH	=	parser2/
PARSER2_SRCS	=	parser2.c get_command.c argument_handlers.c open_file.c get_command_utils.c \
                    add_command.c crop_line.c dollar_handler.c command_list_utils.c parser_utils.c
EXEC_PATH	=	executor/
EXEC_SRCS	=	executor.c \
				exec_echo.c exec_cd.c exec_pwd.c exec_env.c \
				exec_export_args_0_0.c exec_export_args_0_1.c \
				exec_export_args_1_0.c exec_export_args_1_1.c exec_export_args_1_2.c \
				exec_unset.c exec_exit.c completion_code.c \
				executable/executable_1.c executable/executable_2.c \
				pipe/pipe.c
GNL_PATH	=	gnl_dir/
GNL_SRCS	=	get_next_line.c get_next_line_utils.c
SRCS		=	minishell.c fill_all.c signal_handler.c start_all/start_env_shlvl.c\
				$(addprefix $(PARSER2_PATH), $(PARSER2_SRCS)) \
				$(addprefix $(LC_PATH), $(LC_SRCS)) \
				$(addprefix $(EXEC_PATH), $(EXEC_SRCS)) \
				$(addprefix $(LG_PATH), $(LG_SRCS)) \
				$(addprefix $(GNL_PATH), $(GNL_SRCS))
OBJS		=	$(SRCS:.c=.o)
LIB_DIR		=	libft/
HDR			=	includes/*.h
CYAN		=	\x1B[36m
MAGENTA		=	\x1B[35m
GREEN		=	\033[92m
ENDCOLOR	=	\x1B[0m

all:		$(NAME)

$(NAME):	$(OBJS) $(HDR)
			@make bonus -C $(LIB_DIR)
			@mv $(LIB_DIR)$(LIBFT) $(LIBFT)
			@$(CCF) -ltermcap -lreadline $(OBJS) $(LIBFT) -o $(NAME)
			@echo "${GREEN}"$(NAME)" is compiled${ENDCOLOR}"

linux:		$(OBJS) $(HDR)
			@make bonus -C $(LIB_DIR)
			@mv $(LIB_DIR)$(LIBFT) $(LIBFT)
			@$(CCF) -lncurses -lreadline $(OBJS) $(LIBFT) -o $(NAME)
			@echo $(NAME) is compiled

clean:
			@make clean -C $(LIB_DIR)
			@$(RM) $(LIBFT)
			@$(RM) $(OBJS)
			@echo objs deleted

fclean:		clean
			@make fclean -C $(LIB_DIR)
			@$(RM) $(NAME)
			@echo $(NAME) deleted

re:			fclean all

%.o:		%.c $(HDR)
			@$(CCF) -c $< -o $@
			@echo $@ compilled

norm:
			norminette $(SRCS) ./includes

.PHONY:		all clean fclean re so bonus norm
