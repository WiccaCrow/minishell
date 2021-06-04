#include "../includes/line_getter.h"

/**
 * Функция переключает терминал в НЕканонический режим
*/

int		canon_off(void)
{
	struct termios	term;
	
	if (!tcgetattr(0, &term))
	{
		term.c_lflag &= ~(ECHO);
		term.c_lflag &= ~(ICANON);
		if (!tcsetattr(0, TCSANOW, &term))
			return (0);
	}
	return (-1);
}

/**
 * Функция переключает терминал в канонический режим
*/

int		canon_on(void)
{
	struct termios	term;

	if (!tcgetattr(0, &term))
	{
		term.c_lflag |= ECHO;
		term.c_lflag |= ICANON;
		if (!tcsetattr(0, TCSANOW, &term))
			return (0);
	}
	return (-1);
}

