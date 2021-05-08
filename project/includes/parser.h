#ifndef PARSER_H
# define PARSER_H

# define QUOTE 1
# define DOUBLE_QUOTE 2
# define SHIELD 4
# define SPEC_SYMS "\'\"$"

int		get_next_arg(const char *line, int i, char **tmp_line);
int		skip_spaces(const char *line, int i);
int		skip_command(const char *line);

#endif 
