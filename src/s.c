/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 17:47:58 by josh              #+#    #+#             */
/*   Updated: 2018/07/08 00:58:41 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	swapper(t_node **a, t_node **b)
{
	t_node	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	quicksort(t_node **files, int start, int end, t_f *f)
{
	int		pivot;

	if (start < end)
	{
		if (f->t_flag)
		 	pivot = t_partition(files, start, end, f);
		else if (f->us_flag)
		 	pivot = s_partition(files, start, end, f);
		else
		 	pivot = partition(files, start, end, f);
		quicksort(files, start, pivot - 1, f);
		quicksort(files, pivot + 1, end, f);
	}
}