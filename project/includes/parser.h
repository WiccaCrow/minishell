#ifndef PARSER_H
# define PARSER_H

# include "../gnl_dir/get_next_line.h"
# include "../libft/libft.h"

# define WRITE 1
# define APPEND 2
# define READ 4
# define HEREDOC 8
# define NO_FILENAME 16
# define TMP_FILE ".tmp_file"
# define NOFILE_REDIRECT 1
# define WORD 2
# define TOKEN 4

int		skip_spaces(const char *line, int i);
int		crop_line(char **line);
char	*add_chr(char *str, char c);
int		clear_list2(t_list **args);
int		remove_first(t_list **args);
int		set_redirect(const char *word);
int		open_tmp_file(char *stop_str);

#endif 
