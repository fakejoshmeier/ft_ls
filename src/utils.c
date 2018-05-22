/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:20:00 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 14:19:47 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	frito(t_node *leaf, t_f *f)
{
	int				i;

	i = -1;
	if (!f->ur_flag)
		if (leaf->files)
			while (leaf->files[++i])
				ft_free(leaf->files[i]);
	if (leaf->files)
		ft_free(leaf->files);
	ft_free(leaf);
}

int		is_dir(const char *path)
{
	struct stat		statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	putendl_c(char const *s, char *col)
{
	ft_putstr_fd(col, STDOUT_FILENO);
	ft_putstr_fd(s, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	write(1, "\n", 1);
}

void	free_deux(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
	ptr1 = NULL;
	ptr2 = NULL;
}
