/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:39:00 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/17 23:05:56 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

char	*fill_perm(struct stat stats)
{
	char	*ret;

	ret = (char *)ft_memalloc(sizeof(char) * 10);
	ret[0] = (S_ISDIR(stats.st_mode)) ? "d" : "-");
    ret[1] = (stats.st_mode & S_IRUSR) ? "r" : "-");
    ret[2] = (stats.st_mode & S_IWUSR) ? "w" : "-");
    ret[3] = (stats.st_mode & S_IXUSR) ? "x" : "-");
    ret[4] = (stats.st_mode & S_IRGRP) ? "r" : "-");
    ret[5] = (stats.st_mode & S_IWGRP) ? "w" : "-");
    ret[6] = (stats.st_mode & S_IXGRP) ? "x" : "-");
    ret[7] = (stats.st_mode & S_IROTH) ? "r" : "-");
    ret[8] = (stats.st_mode & S_IWOTH) ? "w" : "-");
    ret[9] = (stats.st_mode & S_IXOTH) ? "x" : "-");
	return (ret);
}

t_i		*find_info(t_node *tree, int i)
{
	struct stat		stats;
	struct passwd	*pwd;
	struct group	*grp;
	t_i				*ret;

	if (stat(tree[i]->name, &stats) < 0)
		return (NULL);
	ret = (t_i *)ft_memalloc(sizeof(t_info));
	ret->perm = fill_perm(stats);
	ret->links = stats.st_nlink;
	ret->owner = ((pwd = getpwuid(stats.st_uid))) ? pwd->pw_name : NULL;
	ret->group = ((grp = getgrgid(stats.st_gid))) ? grp->gr_name : NULL;
	ret->size = stats.st_size;
	if (time(NULL) - time(stats->st_mtime) >= 15552000 ||
		time(stats->st_mtime) - time(NULL) >= 15552000)
			ret->time = ft_strjoin(ft_strsub(ctime(stats->st_mtime), 5, 7),
			ft_strsub(ctime(stats->st_mtime), 20, 5));
	else
		ret->time = ft_strsub(ctime(stats->st_mtime), 5, 12);
	ret->owner_num = (int)stats.st_uid;
	ret->group_num = (int)stats.st_gid;
	return (ret);
}

void	print_info(t_node *node, t_f *f)
{
	ft_printf("%s", node->info->perm);
	node->info->thing_flag ? write(1, "@ ", 2) : write(1, "  ", 2); //extended permissions is @, extended security info is "+"
	if (f->n_flag)
		ft_printf("%-8d %-8d", node->info->owner_num, node->info->group_num);
	else
	{
		node->info->owner ? ft_printf("%-8.8s ", node->info->owner) :
		ft_printf("%-8d", node->info->owner_num);
		node->info->group ? ft_printf("%-8.8s ", node->info->group) :
		ft_printf("%-8d", node->info->group_num);
	}
	p
	
}

void	print(t_node *tree, t_f *f)
{
	int		i;

	i = -1;
	if (f->l_flag)
	{
		while (tree->files[++i])
		{
			tree->files[i]->info = find_info(tree, i);
			tree->lt += tree->files[i]->info->links;
		}
		printf("total %d\n", tree->lt);
		i = -1;
	}
	while (tree->files[++i])
	{
		if (tree->files[i]->name[0] == '.' && !f->a_flag)
			continue ;
		if (f->ua_flag && (!ft_strcmp(tree->files[i]->name, ".") ||
			!ft_strcmp(tree->files[i]->name, "..")))
			continue ;
		f->l_flag ?	print_info(tree->files[i]) : 0;
		ft_printf("%s\n", tree->files[i]->name);
	}
}