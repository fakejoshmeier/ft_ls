/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 11:36:25 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/09 00:47:44 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	sort_inputs(t_node **files, t_f *f, int size, int bad)
{
	int		j;
	int		d;

	FUCK(size);
	f->f_flag ? 0 : quicksort(files, 0, size - 1, f);
	d = 0;
	j = -1;
	while (++j < size)
		files[j]->direct ? d++ : ft_printf("%s\n", files[j]->name);
	j = -1;
	while (++j < size)
	{
		if (files[j]->direct)
		{
			j == 0 || !d ? 0 : write(1, "\n", 1);
			if (size > 1 || (size == 1 && bad > 0))
				files[j]->direct ? ft_printf("%s:\n", files[j]->name) : 0;
			files[j]->direct ? create_tree(f, files[j], files[j]->name) : 0;
		}
		OTHERWISE(f_trois(files[j]->path, files[j]->name, files[j]));
	}
	ft_free(files);
}

void	inputs(char *av[], int start, int end, t_f *f)
{
	struct stat	statbuf;
	t_node		**in;
	int			i;
	int			valid;

	if (start > end)
		return ;
	i = start;
	valid = 0;
	f->f_flag ? 0 : quicksart(av, start, end);
	while (i <= end)
	{
		if (lstat(av[i], &statbuf) == -1 && stat(av[i], &statbuf) == -1)
			ft_printf("ft_ls: %s: No such file or directory\n", av[i]);
		else
		{
			in = (t_node **)re(in, (sizeof(t_node *) * (valid + 1)));
			in[valid++] = node_create(av[i], "", f);
		}
		i++;
	}
	sort_inputs(in, f, valid, ((end - start) + 1 - valid));
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
