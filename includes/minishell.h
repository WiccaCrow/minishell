#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

char				*parser(char *line);
int 				executor(char *line);

#endif
