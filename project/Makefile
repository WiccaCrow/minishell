NAME		=	minishell
LIBFT		=	libft.a
CCF			=	gcc $(CFLAGS)
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g
LG_PATH		=	line_getter/
LG_SRCS		=	line_getter.c line_utils.c history_handler.c term_switch.c key_handlers.c
PARSER_PATH	=	parser/
PARSER_SRCS	=	parser.c get_args.c get_next_arg.c dollar_handler.c \
				add_command.c crop_line.c get_command.c
EXEC_PATH	=	executor/
EXEC_SRCS	=	executor.c exec_echo.c exec_cd.c exec_pwd.c exec_env.c \
				exec_export_args_0_0.c exec_export_args_0_1.c exec_export_args_1.c \
				exec_unset.c
GNL_PATH	=	gnl_dir/
GNL_SRCS	=	get_next_line.c get_next_line_utils.c
SRCS		=	minishell.c fill_all.c \
				$(addprefix $(PARSER_PATH), $(PARSER_SRCS)) \
				$(addprefix $(EXEC_PATH), $(EXEC_SRCS)) \
				$(addprefix $(LG_PATH), $(LG_SRCS)) \
				$(addprefix $(GNL_PATH), $(GNL_SRCS))
OBJS		=	$(SRCS:.c=.o)
LIB_DIR		=	libft/
HDR			=	includes/minishell.h $(GNL_PATH)/get_next_line.h
CYAN		=	\x1B[36m
MAGENTA		=	\x1B[35m
GREEN		=	\033[92m
ENDCOLOR	=	\x1B[0m

all:		$(NAME)

$(NAME):	$(OBJS) $(HDR)
			@make bonus -C $(LIB_DIR)
			@mv $(LIB_DIR)$(LIBFT) $(LIBFT)
			@$(CCF) -ltermcap $(OBJS) $(LIBFT) -o $(NAME)
			@echo "${GREEN}"$(NAME)" is compiled${ENDCOLOR}"

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
