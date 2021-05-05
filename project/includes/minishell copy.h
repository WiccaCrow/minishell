#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define NAME "DULCIE&GRVELVA > "
# define NONECOLOR "\x1B[0m"
# define GOLD "\033[40;33m"

typedef struct s_all {
	int		flag_executer;
	int		flag_exit;
	char	*line;
	char	**env_my;
}	t_all;

void	start_all(t_all *all);
void	init_env(t_all *all);
char	*parser(char *line);
int		executor(char *line);
void	exit_clean(t_all *all, int exit_code);

#endif
