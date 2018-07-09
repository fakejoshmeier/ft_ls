/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:51:39 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/09 04:13:19 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	*re(void *ptr, size_t new_size)
{
	void	*new;

	new = (void *)ft_memalloc(new_size);
	if (new == NULL)
		return (NULL);
	if (ptr == NULL)
		return (new);
	new = ft_memcpy(new, ptr, new_size);
	free(ptr);
	ptr = NULL;
	return (new);
}

t_node	*node_create(char *name, char *dir_name, t_f *f)
{
	struct stat	statbuf;
	t_node		*node;
	char		*new;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	MATCH(ft_strcmp(dir_name, "") == 0, new = NULL);
	OTHERWISE(new = ft_strjoin(dir_name, "/"));
	node->path = new != NULL ? ft_strjoin(new, name) : ft_strdup(name);
	lstat(node->path, &statbuf) == -1 ? ft_error(node->path, 1) : 0;
	node->name = ft_strdup(name);
	node->direct = S_ISDIR(statbuf.st_mode) ? 1 : 0;
	node->sym = S_ISLNK(statbuf.st_mode) ? 1 : 0;
	node->size = statbuf.st_size;
	node->ll = INT_MIN;
	node->lo = INT_MIN;
	node->lg = INT_MIN;
	node->len_siz = INT_MIN;
	node->len_on = INT_MIN;
	node->len_gn = INT_MIN;
	node->time = (!f->c_flag && !f->u_flag) ? statbuf.st_mtime : 0;
	MATCH(f->c_flag, node->time = statbuf.st_ctime);
	OR(f->u_flag, node->time = statbuf.st_atime);
	MATCH(new, ft_free(new));
	return (node);
}

void	recurse(t_node *leaf, t_f *f, char *name)
{
	char			*new;
	char			*nnew;

	new = NULL;
	nnew = NULL;
	if (ft_strcmp(".", leaf->name) != 0 && ft_strcmp("..", leaf->name) != 0)
	{
		if (f->a_flag || f->ua_flag)
		{
			new = ft_strjoin(name, "/");
			nnew = ft_strjoin(new, leaf->name);
			ft_printf("\n%s:\n", nnew);
			create_tree(f, leaf, nnew);
			free_deux(new, nnew);
		}
		else if (leaf->name[0] != '.')
		{
			new = ft_strjoin(name, "/");
			nnew = ft_strjoin(new, leaf->name);
			ft_printf("\n%s:\n", nnew);
			create_tree(f, leaf, nnew);
			free_deux(new, nnew);
		}
	}
}

void	create_tree(t_f *ls, t_node *t, char *name)
{
	int				i[2];
	DIR				*open;
	struct dirent	*dir;

	i[0] = 0;
	!(open = opendir(name)) ? ft_error(name, 1) : 0;
	while ((dir = readdir(open)))
	{
		if (dir->d_name[0] == '.' && !ls->a_flag && !ls->ua_flag)
			continue ;
		if (ls->ua_flag && (!ft_strcmp(dir->d_name, ".") ||
			!ft_strcmp(dir->d_name, "..")))
			continue ;
		t->files = (t_node **)re(t->files, (sizeof(t_node *) * (i[0] + 1)));
		t->files[i[0]++] = node_create(dir->d_name, name, ls);
	}
	print(t, ls, i[0]);
	closedir(open);
	i[1] = -1;
	if (ls->ur_flag)
		while (++(i[1]) < i[0])
			t->files[i[1]]->direct && !t->files[i[1]]->sym ?
			recurse(t->files[i[1]], ls, name) :
			f_trois(t->files[i[1]]->name, t->files[i[1]]->path, t->files[i[1]]);
	frito(t, ls, i[0]);
}
