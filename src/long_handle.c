/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:07:01 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/08 23:52:42 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

char	*fill_perm(struct stat stats, char *filename)
{
	char			*ret;
	ssize_t			xattr;

	ret = ft_strnew(11);
	ret[0] = '-';
	MATCH(S_ISDIR(stats.st_mode), ret[0] = 'd');
	OR(S_ISBLK(stats.st_mode), ret[0] = 'b');
	OR(S_ISCHR(stats.st_mode), ret[0] = 'c');
	OR(S_ISFIFO(stats.st_mode), ret[0] = 'p');
	OR(S_ISLNK(stats.st_mode), ret[0] = 'l');
	OR(S_ISSOCK(stats.st_mode), ret[0] = 's');
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

void	timefill(t_i *ret, t_node *root, t_f *f)
{
	if (f->ut_flag)
		ret->datestring = ft_strsub(ctime(&root->time), 4, 20);
	else if (time(NULL) - (root)->time < 15552000)
		ret->datestring = ft_strsub(ctime(&root->time), 4, 12);
	else
		ret->datestring = ft_strjoin(ft_strsub(ctime(&root->time), 4, 7),
		ft_strsub(ctime(&root->time), 19, 5));
}

t_i		*find_info(t_node *tree, int i, t_f *f)
{
	struct stat		stats;
	struct passwd	*pwd;
	struct group	*grp;
	t_i				*ret;

	ret = (t_i *)ft_memalloc(sizeof(t_i));
	NULL_GUARD(lstat(tree->files[i]->path, &stats) == 0);
	pwd = getpwuid(stats.st_uid);
	grp = getgrgid(stats.st_gid);
	timefill(ret, tree->files[i], f);
	ret->perm = fill_perm(stats, tree->files[i]->path);
	if (stats.st_mode & S_ISUID)
		ret->perm[3] = (stats.st_mode & S_IXUSR) ? 's' : 'S';
	if (stats.st_mode & S_ISGID)
		ret->perm[6] = (stats.st_mode & S_IXGRP) ? 'S' : 'l';
	if (stats.st_mode & S_ISVTX)
		ret->perm[9] = (stats.st_mode & S_IXOTH) ? 't' : 'T';
	ret->links = stats.st_nlink;
	ret->owner = (pwd) ? ft_strdup(pwd->pw_name) : NULL;
	ret->group = (grp) ? ft_strdup(grp->gr_name) : NULL;
	ret->size = stats.st_size;
	ret->blocks = stats.st_blocks;
	ret->owner_num = (int)stats.st_uid;
	ret->group_num = (int)stats.st_gid;
	return (ret);
}

void	print_info(t_node *head, t_node *node, t_f *f)
{
	ft_printf("%s %*i ", node->info->perm, head->ll, node->info->links);
	if (f->n_flag)
	{
		ft_printf("%-*d ", head->len_on + 1, node->info->owner_num);
		ft_printf("%-*d", head->len_gn + 1, node->info->group_num);
	}
	else
	{
		node->info->owner ? ft_printf("%-*s ", head->lo + 1, node->info->owner)
		: ft_printf("%-*d ", head->len_on + 1, node->info->owner_num);
		node->info->group ? ft_printf("%-*s", head->lg + 1, node->info->group) :
		ft_printf("%-*d", head->len_gn + 1, node->info->group_num);
	}
	node->info->size == 0 ? ft_printf("%*d", head->len_siz, node->info->size) :
		ft_printf("%*d", head->len_siz + 1, node->info->size);
	ft_printf(" %s ", node->info->datestring);
	ft_free(node->info->perm);
	ft_free(node->info->datestring);
	ft_free(node->info->owner);
	ft_free(node->info->group);
	ft_free(node->info);
}
