/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:20:00 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 19:52:52 by jmeier           ###   ########.fr       */
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
				free_deux(leaf->files[i], leaf->files[i]->name);
	if (leaf->files)
		ft_free(leaf->files);
	ft_free(leaf->name);
	ft_free(leaf);
}

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
