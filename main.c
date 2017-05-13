#include <stdio.h>
#include "libft.h"
#include <math.h>
#include "rt.h"

double	ft_dtoa(char *str)
{
	double	res;
	int		s;
	int		i;

	res = 0;
	i = 0;
	s = (*str == '-' && ++str ? -1 : 1);
	while (ft_isdigit(*str) && *str != '.')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (*str)
		str++;
	while (ft_isdigit(*str))
	{
		res = res * 10 + *str - '0';
		str++;
		i++;
	}
	res /= pow(10, i);
	return (res * s);
}

t_sprite	sprite_pars_line(t_env *env, char *str)
{
	t_sprite	spr;
	int			i;

	i = 0;
	if (ft_strncmp("TREE", str, 4) == 0)
		spr.img = env->bmp[5];
	while (ft_isdigit(str[i]) == 0 && str[i] != '-')
		i++;
	spr.pos_x = ft_dtoa(&line[i]);
	while (str[i] != ' ')
		i++;
	i++;
	spr.pos_y = ft_dtoa(&line[i]);
	return (spr);
}

t_s_list	*pars_sprite(t_env *env, int fd);
{
	char		*line;
	t_s_list	*lst;
	t_sprite	sprite;

	lst = (t_s_list)malloc(sizeof(t_s_list));
	while (get_next_line(fd, &line))
	{
		sprite = sprite_pars_line(env, line);
		create_node(lst, sprite);
	}
	return (begin);
}
