/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:30:57 by gmonein           #+#    #+#             */
/*   Updated: 2017/06/05 00:46:32 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				print_wall_uni(t_env *env, t_ray *ray, int x)
{
	int		color;
	int		i;

	i = ray->draw_start;
	color = env->color[env->pal][ray->side + ray->nside];
	while (i + 10 < ray->draw_end)
	{
		px2img(env->pixels, color, x, i);
		px2img(env->pixels, color, x, i + 1);
		px2img(env->pixels, color, x, i + 2);
		px2img(env->pixels, color, x, i + 3);
		px2img(env->pixels, color, x, i + 4);
		px2img(env->pixels, color, x, i + 5);
		px2img(env->pixels, color, x, i + 6);
		px2img(env->pixels, color, x, i + 7);
		px2img(env->pixels, color, x, i + 8);
		px2img(env->pixels, color, x, i + 9);
		i += 10;
	}
	i--;
	while (++i < ray->draw_end)
		px2img(env->pixels, color, x, i);
}

void				print_roof_uni(t_env *env, t_ray *ray, int x)
{
	int		color;
	int		i;

	i = 0;
	color = env->color[env->pal][4];
	while (i + 10 < ray->draw_start)
	{
		px2img(env->pixels, color, x, i);
		px2img(env->pixels, color, x, i + 1);
		px2img(env->pixels, color, x, i + 2);
		px2img(env->pixels, color, x, i + 3);
		px2img(env->pixels, color, x, i + 4);
		px2img(env->pixels, color, x, i + 5);
		px2img(env->pixels, color, x, i + 6);
		px2img(env->pixels, color, x, i + 7);
		px2img(env->pixels, color, x, i + 8);
		px2img(env->pixels, color, x, i + 9);
		i += 10;
	}
	i--;
	while (++i < ray->draw_start)
		px2img(env->pixels, color, x, i);
}

void				print_floor_uni(t_env *env, t_ray *ray, int x)
{
	int		color;
	int		i;

	i = ray->draw_end;
	color = env->color[env->pal][5];
	while (i + 10 < WIN_H - 1)
	{
		px2img(env->pixels, color, x, i);
		px2img(env->pixels, color, x, i + 1);
		px2img(env->pixels, color, x, i + 2);
		px2img(env->pixels, color, x, i + 3);
		px2img(env->pixels, color, x, i + 4);
		px2img(env->pixels, color, x, i + 5);
		px2img(env->pixels, color, x, i + 6);
		px2img(env->pixels, color, x, i + 7);
		px2img(env->pixels, color, x, i + 8);
		px2img(env->pixels, color, x, i + 9);
		i += 10;
	}
	i--;
	while (++i < WIN_H - 1)
		px2img(env->pixels, color, x, i);
}

int					blend(unsigned char fg[4], unsigned char bg[4])
{
	unsigned int		alpha;
	unsigned int		inv_alpha;
	unsigned char		res[4];

	alpha = fg[3] + 1;
	inv_alpha = 256 - fg[3];
	res[2] = (unsigned char)((alpha * fg[2] + inv_alpha * bg[2]) >> 8);
	res[0] = (unsigned char)((alpha * fg[0] + inv_alpha * bg[0]) >> 8);
	res[1] = (unsigned char)((alpha * fg[1] + inv_alpha * bg[1]) >> 8);
	res[3] = 0xFF;
	return (*(unsigned int *)res);
}

void				set_ray(t_env *env, t_ray *ray, int x)
{
	ray->cam_x = 2 * x / (double)WIN_W - 1;
	ray->pos_x = env->cam.pos_x;
	ray->pos_y = env->cam.pos_y;
	ray->dir_x = env->dir_x + ray->plane_x * ray->cam_x;
	ray->dir_y = env->dir_y + ray->plane_y * ray->cam_x;
	if (x == (int)WIN_W >> 1)
	{
		env->mid_dir_x = ray->dir_x;
		env->mid_dir_y = ray->dir_y;
	}
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->delta_dist_x =
		sqrt(1 + (ray->dir_y * ray->dir_y) / (ray->dir_x * ray->dir_x));
	ray->delta_dist_y =
		sqrt(1 + (ray->dir_x * ray->dir_x) / (ray->dir_y * ray->dir_y));
}
