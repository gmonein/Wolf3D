/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:30:57 by gmonein           #+#    #+#             */
/*   Updated: 2017/06/05 00:44:01 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				set_raystep(t_env *env, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0f - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0f - ray->pos_y) * ray->delta_dist_y;
	}
}

int					launch_ray(t_env *env, t_ray *ray)
{
	while (1)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_x < 0)
			return (-1);
		if (env->map[(int)ray->map_y][(int)ray->map_x] != 0)
			return (env->map[(int)ray->map_y][(int)ray->map_x]);
	}
}

void				get_wall_inf(t_env *env, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist =
			(ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dist =
			(ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	if ((ray->side == 0 && ray->pos_x - ray->map_x < 0)
			|| (ray->side == 1 && ray->pos_y - ray->map_y < 0))
		ray->nside = 2;
	else
		ray->nside = 0;
	ray->line_height = (int)(WIN_H / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + (int)WIN_H / 2;
	ray->draw_end = ray->line_height / 2 + (int)WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= (int)WIN_H)
		ray->draw_end = (int)WIN_H - 1;
}

void				set_side(t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0)
	{
		ray->floor_x_wall = ray->map_x;
		ray->floor_y_wall = ray->map_y + ray->wallx;
	}
	else if (ray->side == 0 && ray->dir_x < 0)
	{
		ray->floor_x_wall = ray->map_x + 1;
		ray->floor_y_wall = ray->map_y + ray->wallx;
	}
	else if (ray->side == 1 && ray->dir_y > 0)
	{
		ray->floor_x_wall = ray->map_x + ray->wallx;
		ray->floor_y_wall = ray->map_y;
	}
	else
	{
		ray->floor_x_wall = ray->map_x + ray->wallx;
		ray->floor_y_wall = ray->map_y + 1;
	}
}

int					raycast(t_env *env, int start, int end)
{
	t_ray	ray;
	int		x;
	int		i;

	ray.plane_x = env->plane_x;
	ray.plane_y = env->plane_y;
	x = start - 1;
	while (++x < end)
	{
		set_ray(env, &ray, x);
		set_raystep(env, &ray);
		ray.hit = launch_ray(env, &ray);
		get_wall_inf(env, &ray);
		print_wall_uni(env, &ray, x);
		print_floor_uni(env, &ray, x);
		print_roof_uni(env, &ray, x);
	}
	return (1);
}
