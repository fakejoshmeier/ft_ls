/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:11:50 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/09 03:54:32 by jmeier           ###   ########.fr       */
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

int		t_partition(t_node **f, int start, int end, t_f *fl)
{
	t_node	*p;
	int		i;
	int		j;

	p = f[end];
	i = (start - 1);
	j = start;
	while (j < end)
	{
		if (fl->r_flag)
		{
			if (f[j]->time == p->time && ft_strcmp(f[j]->name, p->name) > 0)
				swapper(&f[++i], &f[j]);
			OR(f[j]->time < p->time, swapper(&f[++i], &f[j]));
		}
		else
		{
			if (f[j]->time == p->time && ft_strcmp(f[j]->name, p->name) < 0)
				swapper(&f[++i], &f[j]);
			OR(f[j]->time > p->time, swapper(&f[++i], &f[j]));
		}
		++j;
	}
	swapper(&f[i + 1], &f[end]);
	return (i + 1);
}

int		s_partition(t_node **f, int start, int end, t_f *fl)
{
	t_node	*p;
	int		i;
	int		j;

	p = f[end];
	i = (start - 1);
	j = start;
	while (j < end)
	{
		if (fl->r_flag)
		{
			if (f[j]->size == p->size && ft_strcmp(f[j]->name, p->name) > 0)
				swapper(&f[++i], &f[j]);
			OR(f[j]->size < p->size, swapper(&f[++i], &f[j]));
		}
		else
		{
			if (f[j]->size == p->size && ft_strcmp(f[j]->name, p->name) < 0)
				swapper(&f[++i], &f[j]);
			OR(f[j]->size > p->size, swapper(&f[++i], &f[j]));
		}
		++j;
	}
	swapper(&f[i + 1], &f[end]);
	return (i + 1);
}
