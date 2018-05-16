/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:39:00 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/15 17:05:01 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	print(t_node *tree, t_f *f)
{
	int		i;

	i = -1;
	while (tree->files[++i])
	{
		if (f->l_flag)
			ft_printf("%s %-2d %s  %s %-7d %.3s %-2d "); //File status, size, owner, thing, bytes, mon d year or time
		if (tree->files[i]->name[0] == '.' && !f->a_flag)
			continue ;
		if (f->ua_flag && (!ft_strcmp(tree->files[i]->name, ".") ||
			!ft_strcmp(tree->files[i]->name, "..")))
			continue ;
		ft_printf("%s\n", tree->files[i]->name);
	}
}
