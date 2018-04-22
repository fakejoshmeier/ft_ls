/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 20:36:46 by jmeier            #+#    #+#             */
/*   Updated: 2018/04/21 22:50:23 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	stat_thing(dir)
{
	struct stat		statbuf;

	if ((stat(dir->d_name, &statbuf)) == -1)
		ft_error("Unable to get stats somehow.");
	
}

void	do_the_thing(t_ls *ls, char *dir_name)
{
	struct dirent	*dir;
	int				i;

	i = 0;
	ls->open = opendir(dir_name);
	while ((dir = readdir(ls->open)) != NULL)
	{
		if ls->f->a_flag != 1 && dir->d_name[0] == '.'
			continue ;
		stuff_filename_into_list(ls, dir);
		ls->f->ur_flag == 1 ? checks_if_file_is_directory(ls, dir);
		
//	A TREE IS AUTO SORTED THAT IS COOL FUCK THE ARRAY
//  tree
//  *name
//  *stat info I guess.  So depending on the flag, I can go up or go down the tree.
// 
	}
	closedir(ls->open);
	print_ls(ls->files);
	if ()
}