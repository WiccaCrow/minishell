#ifndef PARSER_H
# define PARSER_H

# include "../gnl_dir/get_next_line.h"
#include "../libft/libft.h"

# define WRITE 1
# define APPEND 2
# define READ 4
# define LIM_READ 8
# define NO_FILENAME 16

int		get_next_arg(char *line, int i, char **tmp_line);
int		skip_spaces(const char *line, int i);
int		skip_command(const char *line, int i);
int 	crop_line(char **line);
char	*add_chr(char *str, char c);
int		clear_list2(t_list **args);
int 	remove_first(t_list **args);



#endif 
