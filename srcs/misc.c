/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:30:57 by gmonein           #+#    #+#             */
/*   Updated: 2017/06/05 00:42:39 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	px2img(int *pixels, int clr, int x, int y)
{
	pixels[(int)(WIN_W) * y + x] = clr;
}

int		get_pixel(SDL_Surface *src, int x, int y)
{
	return (*((int *)(1 + src->pixels + y * src->pitch + (x << 2))));
}
