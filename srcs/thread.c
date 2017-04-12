/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:32:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/02 03:02:21 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

pthread_t			**malloc_thread(int count)
{
	pthread_t		**thread;

	thread = (pthread_t **)malloc(sizeof(pthread_t *) * (count + 1));
	thread[count] = NULL;
	while (--count != -1)
		thread[count] = (pthread_t *)malloc(sizeof(pthread_t));
	return (thread);
}

static void			*thread_fonc(void *b)
{
	raycast(
	((struct s_args *)b)->env,
	((struct s_args *)b)->start,
	((struct s_args *)b)->end);
	pthread_exit(NULL);
}

static void			create_thread(t_env *env, pthread_t **thread, int count)
{
	int			x_inc;
	int			x;
	int			ret;
	t_args		args;

	x_inc = WIN_W / count;
	x = 0;
	args.done = 1;
	args.env = env;
	while (--count != -1)
	{
		args.start = x;
		args.end = x + x_inc;
		ret = pthread_create(thread[count], NULL,
			thread_fonc,
			&args);
		x += x_inc;
	}
}

void				redraw(t_env *env)
{
	int		i;
	void	*ret;

	i = -1;
	create_thread(env, env->thread, env->thread_cnt);
	while (env->thread[++i])
		pthread_join(*env->thread[i], &ret);
}
