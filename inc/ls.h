/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:40:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/17 20:51:21 by jmeier           ###   ########.fr       */
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

typedef struct		s_f
{
	int				l_flag;
	int				ur_flag;
	int				a_flag;
	int				ua_flag;
	int				r_flag;
	int				t_flag; //time modified sort.  Most recently modified first, than lexicographical order.
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
	char			*month;
	int				day;
	int				hh;
	int				mm;
	int				yyyy;
	//int				owner_num;
	//int				group_num;
}					t_i;

typedef struct		s_node
{
	struct s_node	**files;
	char			*name;
	int				direct;
}					t_node;

typedef	struct		s_ls
{
	struct s_f		*f;
}					t_ls;

#endif
