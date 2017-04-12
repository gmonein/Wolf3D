
#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	SDL_Surface		*s_back;
	SDL_Surface		*bmp;
	SDL_Renderer	*render;
	SDL_Texture		*texture;
	int				pal;
	int				text;
	int				**map;
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
}                   t_env;

#endif /* structures_h */
