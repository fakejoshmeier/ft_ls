/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:51:39 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/15 16:38:44 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

int		is_dir(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

t_node	*node_create(char *name)
{
	t_node	*node;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	node->name = name;
	node->direct = is_dir(name);
	return (node);
}

void	*create_tree(t_ls *ls, t_node *tree, char *name)
{
	int				i;
	DIR				*open;
	struct dirent	*dir;

	i = 0;
	open = opendir(name);
	tree->files = (t_node **)ft_memalloc(sizeof(t_node *));
	while ((dir = readdir(open)))
	{
		tree->files = (t_node **)ft_realloc(tree->files, (sizeof(t_node *) *
			(i + 1)));
		tree->files[i] = node_create(dir->d_name);
		++i;
	}
	sort(tree->files, ls->f); //Need to know how to sort acc to flags
	print_files(tree, ls->f); //Need to know printing format
	if (ls->f->ur_flag)
	{
		i = -1;
		while (tree->files[++i])
			tree->files[i]->direct ? create_tree(ls, tree->files[i]) : 0;
	}
	closedir(open);
	free(tree);
}
