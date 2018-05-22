/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:39:00 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 04:52:57 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	lengths(t_node *tree, t_i *ret)
{
	tree->ll = (int)ft_numlen(ret->links, 10) > tree->ll ?
		(int)ft_numlen(ret->links, 10) : tree->ll;
	tree->lo = (int)ft_strlen(ret->owner) > tree->lo ?
		(int)ft_strlen(ret->owner) : tree->lo;
	tree->lg = (int)ft_strlen(ret->group) > tree->lg ?
		(int)ft_strlen(ret->group) : tree->lg;
	tree->len_siz = (int)ft_numlen(ret->size, 10) > tree->len_siz ?
		(int)ft_numlen(ret->size, 10) : tree->len_siz;
	tree->len_on = (int)ft_numlen(ret->owner_num, 10) > tree->len_on ?
		(int)ft_numlen(ret->owner_num, 10) : tree->len_on;
	tree->len_gn = (int)ft_numlen(ret->group_num, 10) > tree->len_gn ?
		(int)ft_numlen(ret->group_num, 10) : tree->len_gn;
}

void	print(t_node *tree, t_f *f, int size)
{
	int		i;

	i = -1;
	if (f->l_flag || f->t_flag)
	{
		while (++i < size)
		{
			tree->files[i]->info = find_info(tree, i);
			tree->lt += tree->files[i]->info->size;
			lengths(tree, tree->files[i]->info);
		}
		ft_printf("total %d\n", (tree->lt / 512) + (tree->lt % 512 ? 1 : 0));
		i = -1;
	}
	if (!f->f_flag)
		sort(tree, f, size);
	while (++i < size)
	{
		f->l_flag ? print_info(tree, tree->files[i], f) : 0;
		ft_printf("%s\n", tree->files[i]->name);
	}
}
