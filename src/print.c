/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:39:00 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/09 03:02:23 by jmeier           ###   ########.fr       */
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
	if (ret->dev)
	{
		tree->maj_len = (int)ft_unumlen(ret->maj, 10) > tree->maj_len ?
			(int)ft_numlen(ret->maj, 10) : tree->maj_len;
		tree->min_len = (int)ft_unumlen(ret->min, 10) > tree->min_len ?
			(int)ft_numlen(ret->min, 10) : tree->min_len;
	}
}

/*
** This is a line written for testing since the colored output comes out
** differently compared to the system's
** tree->files[i]->direct ? ft_putendl(tree->files[i]->name) :
** ft_putendl(t->files[i]->name);
*/

void	eat_my_butt_norme(t_node *t, t_f *f, int i)
{
	char	b[1024];
	ssize_t	len;

	if (t->files[i]->sym)
	{
		if (f->l_flag)
		{
			if ((len = readlink(t->files[i]->path, b, sizeof(b) - 1)) != -1)
				b[len] = '\0';
			putendl_c(t->files[i]->name, MAGENTA, 0);
			ft_printf(" -> %s\n", b);
		}
		else
			putendl_c(t->files[i]->name, MAGENTA, 1);
	}
	else if (t->files[i]->direct)
		putendl_c(t->files[i]->name, BLUE, 1);
	else
		ft_putendl(t->files[i]->name);
}

void	smd_norme(t_node *t, t_f *f, int i)
{
	char	b[1024];
	ssize_t	len;

	ft_putstr(t->files[i]->name);
	if (t->files[i]->sym && f->l_flag)
	{
		if ((len = readlink(t->files[i]->path, b, sizeof(b) - 1)) != -1)
			b[len] = '\0';
		ft_printf(" -> %s", b);
	}
	write(1, "\n", 1);
}

void	print(t_node *tree, t_f *f, int size)
{
	int		i;

	i = -1;
	if (f->l_flag)
	{
		while (++i < size)
		{
			tree->files[i]->info = find_info(tree, i, f);
			if (!tree->files[i]->info)
				ft_error("YOU DUN GOOFED BOI", 69);
			tree->lt += tree->files[i]->info->blocks;
			lengths(tree, tree->files[i]->info);
		}
		ft_printf("total %d\n", tree->lt);
		i = -1;
	}
	if (!f->f_flag)
		quicksort(tree->files, 0, size - 1, f);
	while (++i < size)
	{
		f->l_flag ? print_info(tree, tree->files[i], f) : 0;
		f->ug_flag ? eat_my_butt_norme(tree, f, i) : smd_norme(tree, f, i);
	}
}
