#include "rt.h"
#include <fcntl.h>
#include <unistd.h>
int		count_line(int fd)
{
	char	*line;
	int		y;

	y = 1;
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		y++;
	}
	close(fd);
	return (y);
}

int		len_line(char *str)
{
	int		len;
	int		i;

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

int		*pars_line(char *str, int *len)
{
	int		*tab;
	int		i;

	*len = len_line(str);
	tab = (int *)malloc(sizeof(int) * (*len + 2));
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

int		*set_border(int len)
{
	int		*line;
	int		i;

	line = (int *)malloc(sizeof(int) * (len + 2));
	i = -1;
	while (len + 2 > ++i)
		line[i] = -1;
	return (line);
}

int		**parsing(char *file)
{
	int		fd;
	int		y;
	int		**tab;
	int		i;
	char	*line;
	int		len;

	y = count_line(open(file, O_RDONLY)) - 1;
	tab = (int **)malloc(sizeof(int *) * (y + 2));
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
