/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:59:35 by jmeier            #+#    #+#             */
/*   Updated: 2018/04/21 20:33:33 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	ft_error(char *str)
{
	ft_putendl(str);
	exit (0);
}

void	ls_flags(char *str, t_f *f)
{
	char	*poss;
	int		i;
	int		j;

	poss = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	i = 0;
	while (str[++i] && str[i] != '\n')
	{
		j = -1;
		while (poss[++j] && poss[j] != str[i])
			;
		if (j >= strlen(poss))
		{
			ft_printf("ft_ls: illegal option -- %c\n", str[i]);
			ft_error("USAGE: ft_ls [-Ralrt] [file ...]");
		}
		f->l_flag = (str[i] == 'l') ? 1 : 0;
		f->ur_flag = (str[i] == 'R') ? 1 : 0;
		f->a_flag = (str[i] == 'a') ? 1 : 0;
		f->l_flag = (str[i] == 'l') ? 1 : 0;
		f->r_flag = (str[i] == 'r') ? 1 : 0;
	}
}

int		main(int ac, char *av[])
{
	t_ls	*ls;
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			ls_flags(av[i], ls->f);
		else
		{
			i -= 1;
			break ;
		}
	}
	if (i == ac)
	{
		&ls->curr = opendir(".");
		do_the_thing(&ls);
	}
	while (++i < ac)
	{
		&ls->curr = opendir(av[i]);
		do_the_thing(&ls);
	}
	return (0);
}