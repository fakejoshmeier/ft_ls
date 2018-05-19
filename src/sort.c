/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:11:50 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/18 17:43:57 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>


// There is sorting by time of creation, last access, time modified -t, lexicographical
void	sort_by_param(int i, t_node *tree, t_f *f)
{
	t_node	*curr;
	int		j;

	curr = tree->files[i];
	j = i - 1;
	// if (f->t_flag)
	// {
	// 	while (j >= 0 && players[j]->score < curr->score)
	// 	{
	// 		tree->files[j + 1] = tree->files[j];
	// 		--j;
	// 	}
	// }
	// else
	if (!f->t_flag)
	{
		while (j >= 0 && ft_strcmp(curr->name, tree->files[j]->name) < 0)
		{
			tree->files[j + 1] = tree->files[j];
			--j;
		}
	}
	tree->files[j + 1] = curr;
}

void	sort(t_node *tree, t_f *f)
{
	int		i;

	i = -1;
	while (tree->files[++i])
		sort_by_param(i, tree, f);
}