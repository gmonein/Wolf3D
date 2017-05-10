/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:30:57 by gmonein           #+#    #+#             */
/*   Updated: 2017/05/10 22:58:52 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

short		count_line(short fd)
{
	char	*line;
	short		y;

	y = 1;
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		y++;
	}
	close(fd);
	return (y);
}

short	len_line(char *str)
{
	short		len;
	short		i;

	len = 1;
	i = 0;
	while (str[i])
	{
		i++;
		if (ft_isdigit(str[i - 1]) && str[i] == ' ')
			len++;
	}
	return (len);
}

short	*pars_line(char *str, int *len)
{
	short		*tab;
	short		i;

	*len = len_line(str);
	tab = (short *)malloc(sizeof(short) * (*len + 2));
	tab[0] = -1;
	i = 1;
	while (*str && *str != '\n')
	{
		tab[i] = ft_atoi(str);
		str++;
		while (*str && ft_isdigit(*str))
			str++;
		while (*str && *str == ' ')
			str++;
		i++;
	}
	tab[i] = -1;
	return (tab);
}

short		*set_border(short len)
{
	short		*line;
	short		i;

	line = (short *)malloc(sizeof(short) * (len + 2));
	i = -1;
	while (len + 2 > ++i)
		line[i] = -1;
	return (line);
}

short		**parsing(char *file, int *h, int *w)
{
	short		fd;
	short		**tab;
	short		i;
	char		*line;

	*h = count_line(open(file, O_RDONLY)) - 1;
	tab = (short **)malloc(sizeof(short *) * (*h + 2));
	i = 1;
	fd = open(file, O_RDONLY);
	while (i < *h + 1)
	{
		get_next_line(fd, &line);
		tab[i] = pars_line(line, w);
		i++;
		free(line);
	}
	tab[0] = set_border(*w);
	tab[*h + 1] = set_border(*w);
	close(fd);
	return (tab);
}
