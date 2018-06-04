/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:59:35 by jmeier            #+#    #+#             */
/*   Updated: 2018/06/04 16:55:34 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	ft_error(char *str, int i)
{
	if (i == 0)
	{
		ft_printf("ft_ls: illegal option -- %s\n", str);
		ft_putendl("USAGE: ft_ls [-ARSTacflnrtu] [file ...]");
	}
	else if (i == 1)
		ft_printf("ft_ls: %s: No such files or directory\n", str);
	else
		ft_putendl(str);
	(void)str;
	exit(0);
}

void	keep_on_trippin(char c, t_f *f)
{
	c == 'l' ? (f->l_flag = 1) : 0;
	if (c == 'n')
	{
		f->n_flag = 1;
		f->l_flag = 1;
	}
	c == 'r' ? (f->r_flag = 1) : 0;
	c == 't' ? (f->t_flag = 1) : 0;
	if (c == 'u')
	{
		f->c_flag = 0;
		f->u_flag = 1;
	}
}

void	trip_flags(char c, t_f *f)
{
	c == 'A' ? (f->ua_flag = 1) : 0;
	c == 'R' ? (f->ur_flag = 1) : 0;
	c == 'S' ? (f->us_flag = 1) : 0;
	c == 'T' ? (f->ut_flag = 1) : 0;
	c == 'a' ? (f->a_flag = 1) : 0;
	if (c == 'c')
	{
		f->c_flag = 1;
		f->u_flag = 0;
	}
	if (c == 'f')
	{
		f->f_flag = 1;
		f->a_flag = 1;
	}
	keep_on_trippin(c, f);
}

void	ls_flags(char *av[], int *i, t_f *f)
{
	int		j;

	j = 0;
	if (av[*i] && av[*i][0] == '-')
	{
		while (av[*i][++j])
		{
			if (!ft_strchr("ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1", av[*i][j]))
				ft_error(&av[*i][j], 0);
			trip_flags(av[*i][j], f);
		}
		++(*i);
	}
	else
		return ;
	ls_flags(av, i, f);
}

int		main(int ac, char *av[])
{
	t_f		*ls;
	int		i;
	int		tmp;
	char	*new;

	ls = (t_f *)ft_memalloc(sizeof(t_f));
	i = 1;
	new = NULL;
	if (ac > 1)
		ls_flags(av, &i, ls);
			if (ac == 1 || !av[i])
		create_tree(ls, node_create(".", "."), ".");
	tmp = i;
	while (i < ac)
	{
		//tmp == i && tmp < ac - 1 ? do_a_sort(av, i, ac - 1, ls) : 0;
		tmp != ac - 1 ? ft_printf("%s:\n", av[i]) : 0;
		create_tree(ls, node_create(av[i], "."), av[i]);
		i + 1 < ac ? write(1, "\n", 1) : 0;
		i++;
	}
	free(ls);
	return (0);
}
