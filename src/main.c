/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:59:35 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/15 17:03:35 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(0);
}

void	ls_flags(char **av, int *i, t_f *f)
{
	int		j;

	j = -1;
	if (av[*i][0] == '-')
	{
		while (av[*i][++j])
		{
			if (!ft_strchr("ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1", av[*i][j]))
			{
				ft_printf("ft_ls: illegal option -- %c\n", av[*i][j]);
				ft_error("USAGE: ft_ls [-ARalrt] [file ...]");
			}
			f->ua_flag = (av[*i][j] == 'A') ? 1 : 0;
			f->ur_flag = (av[*i][j] == 'R') ? 1 : 0;
			f->a_flag = (av[*i][j] == 'a') ? 1 : 0;
			f->l_flag = (av[*i][j] == 'l') ? 1 : 0;
			f->r_flag = (av[*i][j] == 'r') ? 1 : 0;
			f->t_flag = (av[*i][j] == 't') ? 1 : 0;
		}
		++(*i);
	}
	else
		return ;
	ls_flags(av, i, f);
}

int		main(int ac, char *av[])
{
	t_ls	*ls;
	int		i;

	ls = (t_ls *)ft_memalloc(sizeof(t_ls));
	i = 0;
	ls_flags(av, &i, ls->f);
	if (!av[i] || ac == 1)
		create_tree(ls, node_create("."), ".");
	while (i < ac)
	{
		create_tree(ls, node_create(av[i]));
		i++;
	}
	return (0);
	free(ls);
}
