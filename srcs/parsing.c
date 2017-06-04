/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:30:57 by gmonein           #+#    #+#             */
/*   Updated: 2017/06/05 00:52:39 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

short	**init_int_ttab(int x, int y, int val)
{
	int		i;
	int		j;
	short	**tab;
	short	*line;

	i = -1;
	j = 0;
	tab = (short **)malloc(sizeof(short *) * x);
	line = (short *)malloc(sizeof(short) * x * y);
	while (++i <= y)
	{
		tab[i] = &line[j];
		j += x;
	}
	i = -1;
	j -= x;
	while (++i < j)
	{
		if (i % x == 0 || i % x == 1 || i < x || i > (x - 1) * y)
			line[i] = 1;
		else
			line[i] = (rand() % 5 == 4 ? 1 : 0);
	}
	return (tab);
}

short	**parsing(void)
{
	short	**map;

	map = init_int_ttab(30, 30, 0);
	return (map);
}
