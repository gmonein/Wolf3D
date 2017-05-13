/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:32:27 by gmonein           #+#    #+#             */
/*   Updated: 2017/05/13 22:39:49 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

pthread_t			**malloc_thread(int count, t_args *args, void *a)
{
	pthread_t		**thread;
	int				x;
	int				x_inc;
	int				ret;

	x = 0;
	x_inc = WIN_W / count;
	ret = (int)WIN_W % count;
	thread = (pthread_t **)malloc(sizeof(pthread_t *) * (count + 1));
	thread[count] = NULL;
	while (--count != -1)
	{
		thread[count] = (pthread_t *)malloc(sizeof(pthread_t));
		args[count].env = a;
		args[count].start = x;
		args[count].end = x + x_inc + (ret > 0 ? 1 : 0);
		x += x_inc + (ret > 0 ? 1 : 0);
		ret--;
	}
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
	int			ret;

	while (--count != -1)
		ret = pthread_create(thread[count], NULL,
			thread_fonc, &env->args[count]);
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
