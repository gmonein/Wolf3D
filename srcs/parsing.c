#include "rt.h"
#include <fcntl.h>
#include <unistd.h>
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

short	*pars_line(char *str, short *len)
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

short		**parsing(char *file)
{
	short		fd;
	short		y;
	short		**tab;
	short		i;
	char		*line;
	short		len;

	y = count_line(open(file, O_RDONLY)) - 1;
	tab = (short **)malloc(sizeof(short *) * (y + 2));
	i = 1;
	fd = open(file, O_RDONLY);
	while (i < y + 1)
	{
		get_next_line(fd, &line);
		tab[i] = pars_line(line, &len);
		i++;
		free(line);
	}
	tab[0] = set_border(len);
	tab[y + 1] = set_border(len);
	close(fd);
	return (tab);
}
