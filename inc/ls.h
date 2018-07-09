/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:40:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/08 22:37:43 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include <libft.h>
# include <ft_printf.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <limits.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <stdio.h>

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define MAGENTA "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"

typedef struct		s_f
{
	int				ua_flag;
	int				ur_flag;
	int				us_flag;
	int				ut_flag;
	int				a_flag;
	int				c_flag;
	int				f_flag;
	int				l_flag;
	int				n_flag;
	int				o_flag;
	int				r_flag;
	int				t_flag;
	int				u_flag;
}					t_f;

typedef struct		s_i
{
	char			*perm;
	int				links;
	char			*owner;
	char			*group;
	int				size;
	char			*datestring;
	int				blocks;
	int				owner_num;
	int				group_num;
}					t_i;

typedef struct		s_node
{
	struct s_node	**files;
	char			*name;
	char			*path;
	int				direct;
	int				sym;
	int				lt;
	t_i				*info;
	time_t			time;
	int				size;
	int				ll;
	int				lo;
	int				lg;
	int				len_siz;
	int				len_on;
	int				len_gn;
}					t_node;

int					main(int ac, char *av[]);
void				ls_flags(char **av, int *i, t_f *f);
void				trip_flags(char c, t_f *f);
void				*re(void *ptr, size_t new_size);
void				ft_error(char *str, int i);

void				create_tree(t_f *ls, t_node *tree, char *name);
t_node				*node_create(char *name, char *dir_name, t_f *f);
int					is_dir(const char *path);
void				recurse(t_node *leaf, t_f *f, char *name);
void				frito(t_node *leaf, t_f *f, int size);
void				putendl_c(char const *s, char *col, int i);
void				free_deux(void *ptr1, void *ptr2);
void				f_trois(void *ptr1, void *ptr2, void *ptr3);

void				sort(t_node *tree, t_f *f);
void				quicksort(t_node **files, int low, int high, t_f *f);
int					partition(t_node **files, int low, int high, t_f *f);
int					t_partition(t_node **files, int low, int high, t_f *f);
int					s_partition(t_node **files, int low, int high, t_f *f);
void				swapper(t_node **a, t_node **b);

void				inputs(char *av[], int start, int end, t_f *f);
void				sort_inputs(t_node **files, t_f *f, int size, int bad);
void				swopper(char **a, char **b);
int					portition(char **files, int low, int high);
void				quicksart(char *files[], int low, int high);

void				print(t_node *tree, t_f *f, int size);
void				print_info(t_node *head, t_node *node, t_f *f);
t_i					*find_info(t_node *tree, int i, t_f *f);
char				*fill_perm(struct stat stats, char *filename);
void				lengths(t_node *tree, t_i *ret);

#endif
