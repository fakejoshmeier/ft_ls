/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:59:35 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/18 18:29:41 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(0);
}

void	trip_flags(char c, t_f *f)
{
	f->ua_flag = (c == 'A') ? 1 : 0;
	f->ur_flag = (c == 'R') ? 1 : 0;
	f->a_flag = (c == 'a') ? 1 : 0;
	f->l_flag = (c == 'l') ? 1 : 0;
	if (c == 'n')
	{
		f->n_flag = 1;
		f->l_flag = 1;
	}
	f->r_flag = (c == 'r') ? 1 : 0;
	f->t_flag = (c == 't') ? 1 : 0;
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
			{
				ft_printf("ft_ls: illegal option -- %c\n", av[*i][j]);
				ft_error("USAGE: ft_ls [-ARalnrt] [file ...]");
			}
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
	t_f	*ls;
	int		i;

	ls = (t_f *)ft_memalloc(sizeof(t_f));
	i = 1;
	if (ac > 1)
		ls_flags(av, &i, ls);
	if (ac == 1 || !av[i])
		create_tree(ls, node_create("."), ".");
	while (i < ac)
	{
		create_tree(ls, node_create(av[i]), av[i]);
		i++;
	}
	free(ls);
	return (0);
}
