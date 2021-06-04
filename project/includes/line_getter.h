#ifndef LINE_GETTER_H
# define LINE_GETTER_H

# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define KEY_UP "\e[A"
# define KEY_DOWN "\e[B"
# define KEY_RIGHT "\e[C"
# define KEY_LEFT "\e[D"
# define KEY_BACKSPACE "\177"
# define HIST_FILE "./.hist.txt"

char		**get_history(void);
char 		*show_prev_command(char **history, size_t *pos, char *line, 
				int *hist_pos);
char		*show_next_command(char **history, size_t *pos, char *line, 
				int *hist_pos);
int 		canon_off(void);
int 		canon_on(void);
int 		ft_putchar(int c);
char	 	*add_chr_to_pos(char *str, char c, size_t *pos);
char	 	*remove_chr_from_pos(char *str, size_t *pos);
int			enter_handle(char **line, char **curr_line, size_t *pos);
int 		key_right_handle(char *line, size_t *pos);
int 		key_left_handle(size_t *pos);
char 		*read_history(int fd);
int		    write_history(char **history);
int         clean_history(char **history);
int         add_to_history(char *line, char ***history);
int			history_len(char **history);

#endif
