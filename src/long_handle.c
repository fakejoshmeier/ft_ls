/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:07:01 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 14:14:21 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

char	*fill_perm(struct stat stats, char *filename)
{
	char			*ret;
	ssize_t			xattr;

	ret = ft_strnew(11);
	ret[0] = (S_ISDIR(stats.st_mode)) ? 'd' : '-';
	ret[1] = (stats.st_mode & S_IRUSR) ? 'r' : '-';
	ret[2] = (stats.st_mode & S_IWUSR) ? 'w' : '-';
	ret[3] = (stats.st_mode & S_IXUSR) ? 'x' : '-';
	ret[4] = (stats.st_mode & S_IRGRP) ? 'r' : '-';
	ret[5] = (stats.st_mode & S_IWGRP) ? 'w' : '-';
	ret[6] = (stats.st_mode & S_IXGRP) ? 'x' : '-';
	ret[7] = (stats.st_mode & S_IROTH) ? 'r' : '-';
	ret[8] = (stats.st_mode & S_IWOTH) ? 'w' : '-';
	ret[9] = (stats.st_mode & S_IXOTH) ? 'x' : '-';
	xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
	ret[10] = xattr > 0 ? '@' : ' ';
	return (ret);
}

void	timefill(t_i *ret, struct stat stats, t_f *f)
{
	if (f->c_flag)
		ret->time = stats.st_ctime;
	else if (f->u_flag)
		ret->time = stats.st_atime;
	else
		ret->time = stats.st_mtime;
	if (f->ut_flag && f->l_flag)
		ret->datestring = ft_strsub(ctime(&ret->time), 4, 20);
	else if (time(NULL) - ret->time < 15552000)
		ret->datestring = ft_strsub(ctime(&ret->time), 4, 12);
	else
		ret->datestring = ft_strjoin(ft_strsub(ctime(&ret->time), 4, 7),
		ft_strsub(ctime(&ret->time), 20, 5));
}

t_i		*find_info(t_node *tree, int i, t_f *f)
{
	struct stat		stats;
	struct passwd	*pwd;
	struct group	*grp;
	t_i				*ret;
	// char			*new;

	ret = (t_i *)ft_memalloc(sizeof(t_i));
	// ret->tmp = ft_strjoin(tree->name, "/");
	// new = ft_strjoin(new, tree->files[i]->name);
	if (stat(tree->files[i]->name, &stats) < 0)
		return (NULL);
	pwd = getpwuid(stats.st_uid);
	grp = getgrgid(stats.st_gid);
	timefill(ret, stats, f);
	ret->perm = fill_perm(stats, tree->files[i]->name);
	ret->links = stats.st_nlink;
	ret->owner = (pwd) ? pwd->pw_name : NULL;
	ret->group = (grp) ? grp->gr_name : NULL;
	ret->size = stats.st_size;
	ret->blocks = stats.st_blocks;
	ret->owner_num = (int)stats.st_uid;
	ret->group_num = (int)stats.st_gid;
	// free_deux(new, ret->tmp);
	return (ret);
}

void	print_info(t_node *head, t_node *node, t_f *f)
{
	ft_printf("%s% *i", node->info->perm, head->ll, node->info->links);
	if (f->n_flag)
		ft_printf("%*d % *d", head->len_on + 1, node->info->owner_num,
			head->len_gn + 1, node->info->group_num);
	else
	{
		node->info->owner ? ft_printf("%*s ", head->lo + 1, node->info->owner) :
		ft_printf("%*d ", head->len_on + 1, node->info->owner_num);
		node->info->group ? ft_printf("%*s", head->lg + 1, node->info->group) :
		ft_printf("%*d", head->len_gn + 1, node->info->group_num);
	}
	ft_printf(" %*d", head->len_siz + 1, node->info->size);
	ft_printf(" %s ", node->info->datestring);
	ft_free(node->info->perm);
	ft_free(node->info->datestring);
	ft_free(node->info);
}
