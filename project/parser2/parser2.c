#include "../minishell"

int parser2(t_all *all)
{
	int			i;

	i = 0;
	all->commands = (t_command **)malloc(sizeof (t_command *));
	if (all->commands)
	{
		*all->commands = NULL;
		i = skip_spaces(all->line, i);
		while (all->line && all->line[i] && all->line[i] != ';')
		{
			i = parse_command(all, i);
			i = skip_spaces(all->line, i);
		}
		set_command_to_all(all);
		show_parse_result(all);

		if (all->flag_command)
			crop_line(&(all->line));
	}
	return (1);
}