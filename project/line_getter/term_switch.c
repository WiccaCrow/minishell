#include "line_getter.h"

int	canon_off(void)
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

int	canon_on(void)
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
