/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 11:36:25 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/08 02:30:31 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

char	**sort_inputs(t_node **files, t_f *f, int size)
{
	char	**ret;
	int		i;
	int		j;

	if (size == 0)
		return (NULL);
	ret = (char **)ft_memalloc(sizeof(char*) * size);
	if (!f->f_flag)
		quicksort(files, 0, size - 1, f);
	i = -1;
	while (++i < size)
		ret[i] = ft_strdup(files[i]->name);
	j = -1;
	while (++j)
	{
		ft_free(files[j]->name);
		ft_free(files[j]);
	}
	ft_free(files);
	return (ret);
}

char	**inputs(char *av[], int start, int end, t_f *f)
{
	struct stat	statbuf;
	t_node		**in;
	char		*new;
	int			i;
	int			valid;

	i = start;
	valid = 0;
	if (start > end)
		return (NULL);
	f->f_flag ? 0 : quicksart(av, start, end);
	while (i <= end)
	{
		new = ft_strjoin("./", av[i]);
		if (lstat(new, &statbuf) == -1)
			ft_printf("ft_ls: %s: No such files or directory\n", av[i]);
		else
		{
			in = (t_node **)re(in, (sizeof(t_node *) * (valid + 1)));
			in[valid++] = node_create(av[i], ".", f);
		}
		ft_free(new);
		i++;
	}
	return (sort_inputs(in, f, valid));
}

void	swopper(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		portition(char **files, int start, int end)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = files[end];
	i = (start - 1);
	j = start;
	while (j < end)
	{
		if (ft_strcmp(files[j], pivot) < 0)
			swopper(&files[++i], &files[j]);
		++j;
	}
	swopper(&files[i + 1], &files[end]);
	return (i + 1);
}

void	quicksart(char **files, int start, int end)
{
	int		pivot;

	if (start < end)
	{
		pivot = portition(files, start, end);
		quicksart(files, start, pivot - 1);
		quicksart(files, pivot + 1, end);
	}
}
