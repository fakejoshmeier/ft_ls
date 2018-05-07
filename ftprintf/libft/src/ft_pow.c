/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 00:19:15 by jmeier            #+#    #+#             */
/*   Updated: 2018/02/11 00:22:48 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_pow(int nb, int ex)
{
	if (ex == 0)
		return (1);
	else if (ex < 0)
		return (0);
	return (nb * ft_pow(nb, ex - 1));
}