NAME		=	libft.a
CCF			=	@gcc $(CFLAGS)
MKLIB		=	@ar rc
RM			=	@rm -f
CFLAGS		=	-Wall -Wextra -Werror -c
SRCS		=	ft_memset.c ft_bzero.c ft_memcpy.c \
				ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
				ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
				ft_strrchr.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
				ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
				ft_toupper.c ft_tolower.c ft_strnstr.c ft_calloc.c \
				ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
				ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c
OBJS		=	$(SRCS:.c=.o)
SRCS_BNS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
				ft_lstiter.c ft_lstmap.c ft_lstlast.c
OBJS_BNS	=	$(SRCS_BNS:.c=.o)
HDR			=	libft.h

%.o:		%.c $(HDR)
			$(CCF) -o $@ $<
			@echo $@ compilled

all:		$(OBJS) $(HDR)
			$(MKLIB) $(NAME) $(OBJS)
			ranlib $(NAME)
			@echo libft.a compilled

clean:
			$(RM) $(OBJS) $(OBJS_BNS)
			@echo libft objs deleted

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(NAME:.a=.so)
			@echo $(NAME) deleted


re:			fclean all
			@echo make re done

$(NAME):	all

bonus:		$(OBJS) $(OBJS_BNS) $(HDR)
			$(MKLIB) $(NAME) $(OBJS) $(OBJS_BNS)
			@echo libft.a with bonus compilled



.PHONY:		all clean fclean re so bonus
