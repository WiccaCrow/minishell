#include "minishell.h"

char	*crop_redirect(char *word)
{
	int	i;

	i = 0;
	while (word && word[i] && word[i] != '<' && word[i] != '>')
		i++;
	word[i] = 0;
	return (word);
}

int	handle_pre_fd(t_command *command, char *word)
{
	int	fd;

	if (word && ft_isdigit(word[0]))
	{
		fd = ft_atoi(word);
		if (fd > FOPEN_MAX)
			return (!executable_error_print(crop_redirect(word), BAD_FD, 1));
		if (fd != 1)
		{
			command->redirect_type |= PRE_FD;
			if (command->redirect_type & WRITE || \
				command->redirect_type & APPEND)
				command->output_fd = fd;
			else
				command->input_fd = fd;
		}
	}
	return (1);
}
