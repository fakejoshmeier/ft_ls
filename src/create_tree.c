/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:51:39 by jmeier            #+#    #+#             */
/*   Updated: 2018/06/04 20:52:42 by jmeier           ###   ########.fr       */
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

t_node	*node_create(char *name, char *dir_name)
{
	struct stat	statbuf;	
	t_node		*node;
	char		*new;

	new = ft_strjoin(dir_name, "/");
	node = (t_node *)ft_memalloc(sizeof(t_node));
	node->path = ft_strjoin(new, name);
	if (lstat(node->path, &statbuf) != 0)
		return (0);
	node->name = ft_strdup(name);
	node->direct = S_ISDIR(statbuf.st_mode) ? 1 : 0;
	node->sym = S_ISLNK(statbuf.st_mode) ? 1 : 0;
	node->ll = INT_MIN;
	node->lo = INT_MIN;
	node->lg = INT_MIN;
	node->len_siz = INT_MIN;
	node->len_on = INT_MIN;
	node->len_gn = INT_MIN;
	ft_free(new);
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

void	create_tree(t_f *ls, t_node *tree, char *name)
{
	int				i;
	int				j;
	DIR				*open;
	struct dirent	*dir;

	i = 0;
	!(open = opendir(name)) ? ft_error(name, 1) : 0;
	while ((dir = readdir(open)))
	{
		if (dir->d_name[0] == '.' && !ls->a_flag && !ls->ua_flag)
			continue ;
		if (ls->ua_flag && (!ft_strcmp(dir->d_name, ".") ||
			!ft_strcmp(dir->d_name, "..")))
			continue ;
		tree->files = (t_node **)re(tree->files, (sizeof(t_node *) * (i + 1)));
		tree->files[i++] = node_create(dir->d_name, name);
	}
	print(tree, ls, i);
	closedir(open);
	j = -1;
	if (ls->ur_flag)
		while (++j < i)
			tree->files[j]->direct ? recurse(tree->files[j], ls, name) :
			f_trois(tree->files[j]->name, tree->files[j]->path, tree->files[j]);
	frito(tree, ls, i);
}
