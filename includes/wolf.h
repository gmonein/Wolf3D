/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 06:10:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/06/05 00:53:16 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define WIN_W		1200.0f
# define WIN_H		800.0f
# define D_PAS		0.075f
# define R_PAS		0.05f

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <time.h>
# include "SDL.h"
# include "libft.h"
# include "get_next_line.h"

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_vector_inc
{
	double			dx;
	double			dy;
	double			dif;
}					t_vector_inc;

typedef struct		s_ray
{
	double			floor_x_wall;
	double			floor_y_wall;
	double			cam_x;
	double			pos_x;
	double			pos_y;
	double			map_x;
	double			map_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			side_x;
	double			side_y;
	double			wall_dist;
	double			step_x;
	double			step_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			wallx;
	double			current_floor_x;
	double			current_floor_y;
	double			dist_player;
	double			weight;
	double			current_dist;
	int				floor_text_x;
	int				floor_text_y;
	int				hit;
	int				side;
	int				nside;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct		s_args
{
	struct s_env	*env;
	int				start;
	int				end;
	int				done;
}					t_args;

typedef struct		s_argb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_argb;

typedef struct		s_player
{
	double			axe;
	double			cam_x;
	double			pos_x;
	double			pos_y;
	double			ray_x;
	double			ray_y;
}					t_player;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Cursor		*cursor;
	SDL_Surface		*bmp;
	SDL_Renderer	*render;
	SDL_Texture		*texture;
	SDL_Surface		*sprite;
	SDL_Surface		*screen;
	int				*pixels;
	pthread_t		**thread;
	t_args			*args;
	short			thread_cnt;
	short			pal;
	short			text;
	short			blur;
	short			**map;
	double			dir_x;
	double			old_dir_x;
	double			dir_y;
	double			mid_dir_x;
	double			mid_dir_y;
	double			plane_x;
	double			old_plane_x;
	double			plane_y;
	t_player		cam;
	short			redraw;
	char			run;
	const Uint8		*key;
	int				x;
	int				y;
	int				color[1][6];
	time_t			time;
	time_t			oldtime;
	struct tm		mytime;
}					t_env;

void				ray_trace(t_env *e);
void				px2img(int *color, int clr, int x, int y);
int					raycast(t_env *env, int start, int end);
int					get_pixel(SDL_Surface *src, int x, int y);
pthread_t			**malloc_thread(int count, t_args *args, void *a);
void				redraw(t_env *env);
short				**parsing(void);
int					handle_events(t_env *env);
void				set_ray(t_env *env, t_ray *ray, int x);
int					blend(unsigned char fg[4], unsigned char bg[4]);
void				print_floor_uni(t_env *env, t_ray *ray, int x);
void				print_roof_uni(t_env *env, t_ray *ray, int x);
void				print_wall_uni(t_env *env, t_ray *ray, int x);

#endif
