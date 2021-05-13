#ifndef PARSER_H
# define PARSER_H

# include "../gnl_dir/get_next_line.h"

# define SPEC_SYMS "\'\"$"

int		get_next_arg(char *line, int i, char **tmp_line);
int		skip_spaces(const char *line, int i);
int		skip_command(const char *line);
int 	crop_line(char **line);

#endif 
