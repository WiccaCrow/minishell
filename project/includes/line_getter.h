#ifndef LINE_GETTER_H
# define LINE_GETTER_H

# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>

# define KEY_UP "\e[A"
# define KEY_DOWN "\e[B"
# define KEY_RIGHT "\e[C"
# define KEY_LEFT "\e[D"
# define KEY_BACKSPACE "\177"
# define HIST_FILE "./.hist.txt"

typedef struct			s_line {
	char			*main_line;
	char			*curr_line;
	char			*tmp_line;
	int 			hist_pos;
	int 			hist_len;
	size_t			pos;
}						t_line;

char		**get_history(void);
int			show_prev_command(char **history, t_line *line);
int			show_next_command(char **history, t_line *line);
int 		canon_off(void);
int 		canon_on(void);
int 		ft_putchar(int c);
int 		add_chr_to_pos(t_line *line, char c);
int			remove_chr_from_pos(t_line *line);
int			enter_handle(t_line *line);
int			control_d_handle(t_line *line);
int 		key_right_handle(t_line *line);
int 		key_left_handle(t_line *line);
char 		*rd_history(int fd);
int		    wr_history(char **history);
int         free_char_array(char **history);
int         add_to_history(char *line, char ***history);
int			history_len(char **history);
int			sigint_switcher(t_line *line);


#endif
