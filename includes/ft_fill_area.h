/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_area.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:03:31 by gmonein           #+#    #+#             */
/*   Updated: 2017/02/23 19:08:11 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILL_AREA_H
# define FT_FILL_AREA_H

# include <stdlib.h>

void	*ft_init_fcnt_fill(void);
void	ft_fill_ptr(unsigned *ptr, unsigned fill, int size,
		void (**fcnt_fill)(unsigned *, unsigned));
void	ft_fill_six_teen(unsigned *ptr, unsigned fill);
void	ft_fill_height(unsigned *ptr, unsigned fill);
void	ft_fill_four(unsigned *ptr, unsigned fill);
void	ft_fill_two(unsigned *ptr, unsigned fill);
void	ft_fill_one(unsigned *ptr, unsigned fill);

#endif
