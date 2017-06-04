/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:59:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/06/05 00:14:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		handle_events_a(t_env *env)
{
	int		act;

	act = 0;
	if (env->key[SDL_SCANCODE_W] == 1)
	{
		env->cam.pos_x += (env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x + env->dir_x * D_PAS)]
			== 0 ? D_PAS * env->dir_x : 0);
		env->cam.pos_y += (env->map
			[(int)(env->cam.pos_y + env->dir_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->dir_y : 0);
		act = 1;
	}
	if (env->key[SDL_SCANCODE_S] == 1)
	{
		env->cam.pos_x -= (env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x - env->dir_x * D_PAS)]
			== 0 ? D_PAS * env->dir_x : 0);
		env->cam.pos_y -= (env->map
			[(int)(env->cam.pos_y - env->dir_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->dir_y : 0);
		act = 1;
	}
	return (act);
}

static int		handle_events_b(t_env *env)
{
	int		act;

	act = 0;
	if (env->key[SDL_SCANCODE_D] == 1)
	{
		env->cam.pos_x += (env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x + env->plane_x * D_PAS)]
			== 0 ? D_PAS * env->plane_x : 0);
		env->cam.pos_y += (env->map
			[(int)(env->cam.pos_y + env->plane_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->plane_y : 0);
		act = 1;
	}
	if (env->key[SDL_SCANCODE_A] == 1)
	{
		env->cam.pos_x -= (env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x - env->plane_x * D_PAS)]
			== 0 ? D_PAS * env->plane_x : 0);
		env->cam.pos_y -= (env->map
			[(int)(env->cam.pos_y - env->plane_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->plane_y : 0);
		act = 1;
	}
	return (act);
}

static int		handle_events_c(t_env *env)
{
	int		act;

	act = 0;
	if (env->key[SDL_SCANCODE_RIGHT] == 1)
	{
		env->old_dir_x = env->dir_x;
		env->dir_x = env->dir_x * cos(-R_PAS)
					- env->dir_y * sin(-R_PAS);
		env->dir_y = env->old_dir_x * sin(-R_PAS)
					+ env->dir_y * cos(-R_PAS);
		env->old_plane_x = env->plane_x;
		env->plane_x = env->plane_x * cos(-R_PAS)
						- env->plane_y * sin(-R_PAS);
		env->plane_y = env->old_plane_x * sin(-R_PAS)
						+ env->plane_y * cos(-R_PAS);
		act = 1;
	}
	return (act);
}

int				handle_events(t_env *env)
{
	int		act;

	act = 0;
	act += handle_events_a(env);
	act += handle_events_b(env);
	act += handle_events_c(env);
	if (env->key[SDL_SCANCODE_LEFT] == 1)
	{
		env->old_dir_x = env->dir_x;
		env->dir_x = env->dir_x * cos(R_PAS)
					- env->dir_y * sin(R_PAS);
		env->dir_y = env->old_dir_x * sin(R_PAS)
					+ env->dir_y * cos(R_PAS);
		env->old_plane_x = env->plane_x;
		env->plane_x = env->plane_x * cos(R_PAS)
						- env->plane_y * sin(R_PAS);
		env->plane_y = env->old_plane_x * sin(R_PAS)
						+ env->plane_y * cos(R_PAS);
		act = 1;
	}
	return ((act > 0 ? 1 : 0));
}
