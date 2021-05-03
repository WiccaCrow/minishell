#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"


typedef struct s_stack
{
	int				num;
	int				steps;
	int				mid_dist;
	char			flag;
	struct s_stack	*prev;
	struct s_stack	*next;

}					t_stack;

typedef struct s_all
{
	t_stack			**stk_a;
	t_stack			**stk_b;
	int				min;
	int				max;
	int				mid;
}					t_all;

char				*parser(char *line);
int 				executor(char *line);


#endif
