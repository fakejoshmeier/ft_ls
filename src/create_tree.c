/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:51:39 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 14:18:45 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

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
		tree->files[i] = node_create(dir->d_name);
		++i;
	}
	print(tree, ls, i);
	closedir(open);
	i = -1;
	if (ls->ur_flag)
		while (tree->files[++i] != NULL)
			tree->files[i]->direct ? recurse(tree->files[i], ls, name) :
			ft_free(tree->files[i]);
	frito(tree, ls);
}
