/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:51:39 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 08:04:10 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	frito(t_node *leaf)
{
	int				i;

	i = -1;
	if (leaf->files)
		while (leaf->files[++i])
			ft_free(leaf->files[i]);
	ft_free(leaf->files);
	ft_free(leaf);
}

int		is_dir(const char *path)
{
	struct stat		statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

t_node	*node_create(char *name)
{
	t_node		*node;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	node->name = name;
	node->direct = is_dir(name);
	node->ll = INT_MIN;
	node->lo = INT_MIN;
	node->lg = INT_MIN;
	node->len_siz = INT_MIN;
	node->len_on = INT_MIN;
	node->len_gn = INT_MIN;
	return (node);
}

void	recurse(t_node *leaf, t_f *f, char *name)
{
	char			*new;

	new = NULL;
	if (ft_strcmp(".", leaf->name) != 0 && ft_strcmp("..", leaf->name) != 0)
	{
		if (f->a_flag || f->ua_flag)
		{
			new = ft_strjoin(name, "/");
			new = ft_strjoin(new, leaf->name);
			ft_printf("\n%s:\n", new);
			create_tree(f, leaf, new);
			free(new);
			new = NULL;
		}
		else if (leaf->name[0] != '.')
		{
			new = ft_strjoin(name, "/");
			new = ft_strjoin(new, leaf->name);
			ft_printf("\n%s:\n", new);
			create_tree(f, leaf, new);
			free(new);
			new = NULL;
		}
	}
}

void	create_tree(t_f *ls, t_node *tree, char *name)
{
	int				i;
	DIR				*open;
	struct dirent	*dir;

	i = 0;
	if (!(open = opendir(name)))
	{
		ft_printf("ft_ls: %s: No such files or directory", name);
		ft_error(".");
	}
	while ((dir = readdir(open)))
	{
		if (dir->d_name[0] == '.' && !ls->a_flag && !ls->ua_flag)
			continue ;
		if (ls->ua_flag && (!ft_strcmp(dir->d_name, ".") ||
			!ft_strcmp(dir->d_name, "..")))
			continue ;
		tree->files = (t_node **)re(tree->files, (sizeof(t_node *) * (i + 1)));
		tree->files[i] = node_create(dir->d_name);
		++i;
	}
	print(tree, ls, i);
	closedir(open);
	if (ls->ur_flag)
	{
		i = -1;
		while (tree->files[++i] != NULL)
			tree->files[i]->direct ? recurse(tree->files[i], ls, name) :
			ft_free(tree->files[i]);
	}
	frito(tree);
}
