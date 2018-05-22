/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:59:35 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 08:06:58 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(0);
}

void	*re(void *ptr, size_t new_size)
{
	void	*new;

	new = (void *)ft_memalloc(new_size);
	if (new == NULL)
		return (NULL);
	new = ft_memcpy(new, ptr, new_size);
	free(ptr);
	ptr = NULL;
	return (new);
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
				ft_error("USAGE: ft_ls [-ARSTacflnrtu] [file ...]");
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
	t_f		*ls;
	int		i;
	char	*new;

	ls = (t_f *)ft_memalloc(sizeof(t_f));
	i = 1;
	new = NULL;
	if (ac > 1)
		ls_flags(av, &i, ls);
	if (ac == 1 || !av[i])
		create_tree(ls, node_create("."), ".");
	while (i < ac)
	{
		ft_printf("%s:\n", av[i]);
		new = ft_strjoin("./", av[i]);
		create_tree(ls, node_create(new), new);
		ft_free(new);
		write(1, "\n", 1);
		i++;
	}
	free(ls);
	while (10);
	return (0);
}
