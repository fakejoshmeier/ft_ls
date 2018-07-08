/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:11:50 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/08 01:17:19 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

int		partition(t_node **files, int start, int end, t_f *f)
{
	t_node	*pivot;
	int		i;
	int		j;

	pivot = files[end];
	i = (start - 1);
	j = start;
	while (j < end)
	{
		if (f->r_flag)
		{
			if (ft_strcmp(files[j]->name, pivot->name) > 0)
				swapper(&files[++i], &files[j]);
		}
		else
		{
			if (ft_strcmp(files[j]->name, pivot->name) < 0)
				swapper(&files[++i], &files[j]);
		}
		++j;
	}
	swapper(&files[i + 1], &files[end]);
	return (i + 1);
}

int		t_partition(t_node **files, int start, int end, t_f *f)
{
	t_node	*pivot;
	int		i;
	int		j;

	pivot = files[end];
	i = (start - 1);
	j = start;
	while (j < end)
	{
		if (f->r_flag)
		{
			if (files[j]->time < pivot->time)
				swapper(&files[++i], &files[j]);
		}
		else
		{
			if (files[j]->time > pivot->time)
				swapper(&files[++i], &files[j]);
		}
		++j;
	}
	swapper(&files[i + 1], &files[end]);
	return (i + 1);
}

int		s_partition(t_node **files, int start, int end, t_f *f)
{
	t_node	*pivot;
	int		i;
	int		j;

	pivot = files[end];
	i = (start - 1);
	j = start;
	while (j < end)
	{
		if (f->r_flag)
		{
			if (files[j]->size < pivot->size)
				swapper(&files[++i], &files[j]);
		}
		else
		{
			if (files[j]->size > pivot->size)
				swapper(&files[++i], &files[j]);
		}
		++j;
	}
	swapper(&files[i + 1], &files[end]);
	return (i + 1);
}