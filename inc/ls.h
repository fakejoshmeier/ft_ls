/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:40:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/18 18:49:39 by jmeier           ###   ########.fr       */
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
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <stdio.h>

typedef struct		s_f
{
	int				l_flag;
	int				ur_flag;
	int				a_flag;
	int				ua_flag;
	int				r_flag;
	int				t_flag; //time modified sort.  Most recently modified first, than lexicographical order.
	int				n_flag;
	//int				s_flag;
	//A flag for size sorting rather than
}					t_f;

typedef struct		s_i
{
	char			*perm;
	int				links; //number of links
	char			*owner;
	char			*group;
	int				size; //in bytes
	char			*datestring;
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
}					t_node;

typedef	struct		s_ls
{
	struct s_f		*f;
}					t_ls;

int					main(int ac, char *av[]);
void				ls_flags(char **av, int *i, t_f *f);
void				trip_flags(char c, t_f *f);
void				ft_error(char *str);

void				create_tree(t_f *ls, t_node *tree, char *name);
t_node				*node_create(char *name);
int					is_dir(const char *path);

void				sort(t_node *tree, t_f *f);
void				sort_by_param(int i, t_node *tree, t_f *f);

void				print(t_node *tree, t_f *f);
void				print_info(t_node *node, t_f *f);
t_i					*find_info(t_node *tree, int i);
char				*fill_perm(struct stat stats, char *filename);
#endif
