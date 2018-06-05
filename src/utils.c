/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:20:00 by jmeier            #+#    #+#             */
/*   Updated: 2018/06/04 20:21:26 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	frito(t_node *leaf, t_f *f, int size)
{
	int				i;

	i = -1;
	(void)f;
	if (!f->ur_flag)
		if (leaf->files)
			while (++i < size)
				f_trois(leaf->files[i]->path, leaf->files[i]->name,
				leaf->files[i]);
	if (leaf->files)
		ft_free(leaf->files);
	ft_free(leaf->path);
	ft_free(leaf->name);
	ft_free(leaf);
}

void	putendl_c(char const *s, char *col, int i)
{
	ft_putstr_fd(col, STDOUT_FILENO);
	ft_putstr_fd(s, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	if (i)
		write(1, "\n", 1);
}

void	free_deux(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
	ptr1 = NULL;
	ptr2 = NULL;
}

void	f_trois(void *ptr1, void *ptr2, void *ptr3)
{
	free(ptr1);
	free(ptr2);
	free(ptr3);
	ptr1 = NULL;
	ptr2 = NULL;
	ptr3 = NULL;
}
