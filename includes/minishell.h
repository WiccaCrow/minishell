#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "../libft/libft.h"
# include "../gnl_dir/get_next_line.h"

# define SWAP_A "sa\n"
# define SWAP_B "sb\n"
# define SWAP_BOTH "ss\n"
# define PUSH_A "pa\n"
# define PUSH_B "pb\n"
# define ROT_A "ra\n"
# define ROT_B "rb\n"
# define ROT_BOTH "rr\n"
# define RROT_A "rra\n"
# define RROT_B "rrb\n"
# define RROT_BOTH "rrr\n"
# define STRWAY 1
# define REVWAY 2
# define DIFWAY 4

typedef struct s_stack
{
	int				num;
	int				steps;
	int				mid_dist;
	char			flag;
	struct s_stack	*prev;
	struct s_stack	*next;

}					t_stack;

typedef struct s_all
{
	t_stack			**stk_a;
	t_stack			**stk_b;
	int				min;
	int				max;
	int				mid;
}					t_all;

void				ft_stkadd_back(t_stack **stk, t_stack *new);
void				ft_stkadd_front(t_stack **stk, t_stack *new);
void				ft_stkclear(t_stack **stk);
t_stack				*ft_stklast(t_stack *stk);
t_stack				*ft_stknew(int num);
int					ft_stksize(t_stack **stk);
t_stack				*ft_stkmin(t_stack **stk);
int					is_int(char *str);
int					is_stk_sorted(t_stack **stk);
int					get_stack(t_stack **stk, int argc, char *argv[]);
int					has_double(t_stack **stk, int num);
int					do_sort(t_stack **stk_a, t_stack **stk_b);
int					check_line(char *line);
int					swap(t_stack **stk);
int					push(t_stack **stk_a, t_stack **stk_b);
int					rotate(t_stack **stk);
int					rev_rotate(t_stack **stk);
char				*sort_stack(t_all *all);
char				*five_sort(t_all *all);
char				*four_sort(t_all *all);
char				*three_sort(t_stack **stk_a);
void				do_stack_ops(t_stack **stk_a, t_stack **stk_b,
						char *ops_line, int i);
char				*ultimate_sort(t_all *all);
void				get_each_steps(t_all *all);
int					get_str_steps(t_all *all, int num);
int					get_rev_steps(t_all *all, int num);
char				*do_min_steps(t_all *all, char *ol);
int					check_pos(t_stack *curr, int num, int min, int max);
char				*str_prepare(t_all *all, int num);
char				*rev_prepare(t_all *all, int num);
char				*dif_prepare(t_all *all, int num);
char				*final_rotate(t_stack **stk);
t_stack				*ft_stkmin(t_stack **stk);
t_stack				*ft_stkmax(t_stack **stk);
int					ft_stkmid(t_stack **stk);

#endif
