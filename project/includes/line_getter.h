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

char		**get_history(void);
char 		*show_prev_command(char **history, size_t *pos, char *line);
char		*show_next_command(char **history, size_t *pos, char *line);
int 		canon_off(void);
int 		canon_on(void);
int 		ft_putchar(int c);


#endif
