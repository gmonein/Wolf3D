/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:59:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/06/05 01:17:12 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		free_for_all(t_env *env)
{
	int		i;

	i = -1;
	free(env->map[0]);
	free(env->map);
	free(env->pixels);
	SDL_DestroyRenderer(env->render);
	SDL_DestroyWindow(env->win);
	SDL_DestroyTexture(env->texture);
	free(env->args);
	while (++i < env->thread_cnt)
		free(env->thread[i]);
	free(env->thread);
}

static int	global_loop(t_env *env)
{
	while (env->run)
	{
		SDL_PollEvent(&env->event);
		if (env->event.type == 256)
			env->run = 0;
		if (env->event.window.type == SDL_WINDOWEVENT_CLOSE
				|| env->event.key.keysym.sym == SDLK_ESCAPE
				|| env->event.type == SDL_QUIT)
			env->run = 0;
		handle_events(env);
		redraw(env);
		SDL_UpdateTexture(env->texture, NULL, env->pixels, (int)WIN_W << 2);
		SDL_RenderCopy(env->render, env->texture, NULL, NULL);
		SDL_RenderPresent(env->render);
		env->key = SDL_GetKeyboardState(NULL);
	}
	free_for_all(env);
	exit(1);
	return (0);
}

int			init(t_env *env)
{
	env->cam.pos_x = 3.5;
	env->cam.pos_y = 3.5;
	env->dir_x = 1;
	env->dir_y = 0;
	env->plane_x = 0;
	env->plane_y = -0.66f;
	env->x = 0;
	env->y = 0;
	env->run = 1;
	env->pal = 0;
	env->blur = 1;
	env->color[0][0] = 0xDEE9ED;
	env->color[0][1] = 0xC6C7CB;
	env->color[0][2] = 0x808387;
	env->color[0][3] = 0x71EBAF;
	env->color[0][4] = 0x42A857;
	env->color[0][5] = 0x332F3B;
	env->thread_cnt = 16;
	if (!(env->args = (t_args *)malloc(sizeof(t_args) * (env->thread_cnt + 1))))
		return (0);
	env->thread = malloc_thread(env->thread_cnt, env->args, env);
	if (!(env->key = SDL_GetKeyboardState(NULL)))
		return (0);
	return (1);
}

int			init_sdl(t_env *env)
{
	if (SDL_Init(SDL_INIT_EVENTS) == -1)
		return (0);
	if (!(env->win = SDL_CreateWindow("Wolf3D", 0, 0, WIN_W, WIN_H, 0)))
		return (0);
	env->render = SDL_CreateRenderer(env->win, 0,
			SDL_RENDERER_TARGETTEXTURE
			| SDL_RENDERER_SOFTWARE
			| SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(env->render, 0xC0, 0, 0, 255);
	SDL_RenderClear(env->render);
	SDL_RenderPresent(env->render);
	if (!(env->pixels = (int *)malloc(sizeof(int) * (WIN_H * WIN_W))))
		return (0);
	if (!(env->texture = SDL_CreateTexture(env->render,
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					WIN_W, WIN_H)))
		return (0);
	SDL_SetRenderTarget(env->render, env->texture);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		**map;
	int		*pixels;

	if (!(env.map = parsing()))
		return (0);
	if (!init(&env))
		return (0);
	if (!init_sdl(&env))
		return (0);
	return (global_loop(&env));
}
