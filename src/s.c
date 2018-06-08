/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josh <jmeier@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 17:47:58 by josh              #+#    #+#             */
/*   Updated: 2018/06/07 19:09:12 by josh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	swapper(t_node **files, int a, int b)
{
	t_node	*tmp;

	tmp = files[a];
	players[a] = players[b];
	players[b] = tmp;
}

int		partition(t_node *tree, int low, int high, t_f *f)
{
	t_node	*tmp;
	int		i;
	int		j;

	tmp = tree->files[high];
	i = low;
	j = low - 1;
	while (++j < high)
	{
		if (f->t_flag && tree->files[j]->time > tmp->time)
			swapper(tree->files, i, j);
//			get times for tmp and files j // perhaps put this in node
		else if (!f->t_flag && ft_strcmp(tree->files[j]->name, tmp->name) > 0)
			swapper(tree->files, i, j);
		++i;
	}
	swapper(players, high, i);
	return (i);
}

int		r_partition(t_node *tree, int low, int high, t_f *f)
{
	t_node	*tmp;
	int		i;
	int		j;

	tmp = tree->files[high];
	i = low;
	j = low - 1;
	while (++j < high)
	{
		if (f->t_flag && tree->files[j]->time < tmp->time)
			swapper(tree->files, i, j);
		else if (!f->t_flag && ft_strcmp(tree->files[j]->name, tmp->name) < 0)
			swapper(tree->files, i, j);
		++i;
	}
	swapper(players, high, i);
	return (i);
}

void	quicksort(t_node *tree, int low, int high, t_f *f)
{
	int		pivot;

	while (low < high)
	{
		pivot = f->r_flag ? r_partition(tree, low, high, f) :
		partition(tree, low, high, f);
		if (pivot - low < high - pivot)
		{
			quicksort(players, low, pivot - 1, f);
			low = pivot + 1;
		}
		else
		{
			quicksort(players, pivot + 1, high, f);
			high = pivot - 1;
		}
	}
}

void	sort(t_node *tree, t_f *f)
{
	int		i;

	i = -1;
	while (tree->files[++i]);
		quicksort(players, 0, i - 1, f);
}
