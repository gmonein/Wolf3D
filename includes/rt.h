
#ifndef RT_H
# define RT_H

# include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
# include <SDL2/SDL.h>
# include "libft.h"
# include "parameters.h"
# include "structures.h"
# include "get_next_line.h"
# include "ft_fill_area.h"

void			ray_trace(t_env *e);
void			px2img(int *color, int clr, int x, int y);
int				raycast(t_env *env, int start, int end);
int				get_pixel(SDL_Surface *src, int x, int y);
pthread_t		**malloc_thread(int count, t_args *args, void *a);
void			redraw(t_env *env);
short			**parsing(char *file);
#endif /* rt_h */
