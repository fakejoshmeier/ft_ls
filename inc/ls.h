/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:40:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 04:42:18 by jmeier           ###   ########.fr       */
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

typedef struct		s_f
{
	int				ua_flag;
	int				ur_flag;
	int				us_flag; //size sort
	int				a_flag;
	int				f_flag; //Don't sort.  Turns on a_flag.
	int				l_flag;
	int				n_flag; //No group/user names.  Just numbers.
	int				o_flag; //removes the group from printing in long format
	int				p_flag; //writes a / after directory names
	int				r_flag; //reverse the sort, default is lexicographical
	int				s_flag; //print total number of blocks and blocks per file
	int				t_flag; //time sort
}					t_f;

typedef struct		s_i
{
	char			*perm;
	int				links; //number of links
	char			*owner;
	char			*group;
	int				size; //in bytes
	char			*datestring;
	int				blocks;
	int				owner_num;
	int				group_num;
}					t_i;

typedef struct		s_node
{
	struct s_node	**files;
	char			*name;
	int				direct;
	int				lt;
	t_i				*info;
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
void				ft_error(char *str);

void				create_tree(t_f *ls, t_node *tree, char *name);
t_node				*node_create(char *name);
int					is_dir(const char *path);

void				sort(t_node *tree, t_f *f, int size);
void				sort_by_param(int i, t_node *tree, t_f *f);

void				print(t_node *tree, t_f *f, int size);
void				print_info(t_node *head, t_node *node, t_f *f);
t_i					*find_info(t_node *tree, int i);
char				*fill_perm(struct stat stats, char *filename);
void				lengths(t_node *tree, t_i *ret);

#endif
