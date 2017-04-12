
#ifndef RT_H
# define RT_H

/*
** -------------------------- External Headers ---------------------------------
*/

# include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>

/*
** -------------------------- Internal Libraries -------------------------------
*/


/*
** ------------------------- Internal Frameworks -------------------------------
*/

//# include <SDL/SDL.h>
# include <SDL2/SDL.h>
//# include <SDL2/TTF.h>

/*
** --------------------------- Internal Headers --------------------------------
*/

# include "parameters.h"
# include "structures.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_fill_area.h"
/*
** -----------------------------------------------------------------------------
** ------------------------------- Sources -------------------------------------
** -----------------------------------------------------------------------------
*/

int		**parsing(char *str);
void	ray_trace(t_env *e);
void	px2img(SDL_Renderer *render, int clr, int x, int y);
int		raycast(t_env *env, int start, int end);
int		get_pixel(SDL_Surface *src, int x, int y);
pthread_t			**malloc_thread(int count);
void				redraw(t_env *env);
#endif /* rt_h */
