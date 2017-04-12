/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_area.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:02:32 by gmonein           #+#    #+#             */
/*   Updated: 2017/02/23 19:08:12 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fill_area.h"

void	*ft_init_fcnt_fill(void)
{
	void		(**fcnt_fill)(unsigned *ptr, unsigned fill);
	int			size;

	size = sizeof(void (*)(unsigned *, unsigned)) * 5;
	fcnt_fill = (void (**)(unsigned *, unsigned))malloc(size);
	fcnt_fill[0] = (void *)ft_fill_six_teen;
	fcnt_fill[1] = (void *)ft_fill_height;
	fcnt_fill[2] = (void *)ft_fill_four;
	fcnt_fill[3] = (void *)ft_fill_two;
	fcnt_fill[4] = (void *)ft_fill_one;
	return (fcnt_fill);
}

void	ft_fill_ptr(unsigned *ptr, unsigned fill, int size,
			void (**fcnt_fill)(unsigned *, unsigned))
{
	short	nb_tour;
	short	ret;

	ret = 16;
	if (size < 1 || fcnt_fill == NULL)
		return ;
	while (size != -1 && ret != 0)
	{
		while (size - ret >= 0 && ret != 0)
		{
			fcnt_fill[nb_tour](ptr, fill);
			size -= ret;
			ptr += ret;
		}
		ret /= 2;
		nb_tour++;
	}
}
