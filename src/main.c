/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:59:35 by jmeier            #+#    #+#             */
/*   Updated: 2018/04/19 18:43:29 by jmeier           ###   ########.fr       */
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
		f->
	}
}

int		main(int ac, char *av[])
{
	t_ls	*ls;
	int		i;

	i = -1;
	if (ac == 1)
		&ls->curr = opendir(".");
	else if (ac > 1)
	{
		if (av > 2)
		{
			av[2][0] == '-' ? ls_flags(av[1], ls->f);
			i = 1;
		}
		i = 0;
	}
}