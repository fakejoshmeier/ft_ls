/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:51:39 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/20 13:14:32 by josh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

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
	return (node);
}

void	leaf_free_or_die_hard(t_node *leaf)
{
	free(leaf->name);
	free(leaf->info);
	free(leaf->files);
	free(leaf);
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
		}
		else if (leaf->name[0] != '.')
		{
			new = ft_strjoin(name, "/");
			new = ft_strjoin(new, leaf->name);
			ft_printf("\n%s:\n", new);
			create_tree(f, leaf, new);
			free(new);
		}
	}
	leaf_free_or_die_hard(leaf);
}

void	create_tree(t_f *ls, t_node *tree, char *name)
{
	int				i;
	DIR				*open;
	struct dirent	*dir;

	i = 0;
	open = opendir(name);
	tree->files = (t_node **)ft_memalloc(sizeof(t_node *));
	while ((dir = readdir(open)))
	{
		tree->files = (t_node **)ft_realloc(tree->files, (sizeof(t_node *) * i)
		, (sizeof(t_node *) * (i + 1)));
		tree->files[i] = node_create(dir->d_name);
		++i;
	}
	print(tree, ls);
	closedir(open);
	if (ls->ur_flag)
	{
		i = -1;
		while (tree->files[++i])
			tree->files[i]->direct ? recurse(tree->files[i], ls, name) :
			leaf_free_or_die_hard(tree->files[i]);
	}
	free(tree);
}
