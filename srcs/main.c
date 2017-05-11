
#include "rt.h"
#include <signal.h>
#define D_PAS 0.075f
#define R_PAS 0.05f

int	SDL_EnableKeyRepeat(int a, int b);

void	px2img(int *pixels, int clr, int x, int y)
{
	pixels[(int)(WIN_W) * y + x] = clr;
}

int		get_pixel(SDL_Surface *src, int x, int y)
{
	return (*((int *)(1 + src->pixels + y * src->pitch + (x << 2))));
}

void	print_map(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (++i < env->map_h)
	{
		j = 0;
		while (++j < env->map_w)
		{
			if (j != env->map_w)
				printf("%d ", env->map[i][j]);
			else
				printf("%d", env->map[i][j]);
		}
		printf("\n");
		i++;
	}
}

void	ft_clear_zbuffer(t_env *env)
{
	int		i;
	int		end;
	int		val;

	end = WIN_H * WIN_W;
	i = 0;
	val = INT_MAX;
	while (i < end)
	{
		env->zbuffer[0][i] = val;
		env->zbuffer[0][i + 1] = val;
		env->zbuffer[0][i + 2] = val;
		env->zbuffer[0][i + 3] = val;
		env->zbuffer[0][i + 4] = val;
		env->zbuffer[0][i + 5] = val;
		env->zbuffer[0][i + 6] = val;
		env->zbuffer[0][i + 7] = val;
		env->zbuffer[0][i + 8] = val;
		env->zbuffer[0][i + 9] = val;
		i += 10;
	}
}

static int handle_events(t_env *env)
{
	int		act;

	act = 0;
	if (env->key[SDL_SCANCODE_W] == 1)
	{
		env->cam.pos_x +=
			(env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x + env->dir_x * D_PAS)]
			== 0 ? D_PAS * env->dir_x : 0);
		env->cam.pos_y +=
			(env->map
			[(int)(env->cam.pos_y + env->dir_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->dir_y : 0);
			act = 1;
	}
	if (env->key[SDL_SCANCODE_S] == 1)
	{
		env->cam.pos_x -=
			(env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x - env->dir_x * D_PAS)]
			== 0 ? D_PAS * env->dir_x : 0);
		env->cam.pos_y -=
			(env->map
			[(int)(env->cam.pos_y - env->dir_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->dir_y: 0);
			act = 1;
	}
	if (env->key[SDL_SCANCODE_D] == 1)
	{
		env->cam.pos_x +=
			(env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x + env->plane_x * D_PAS)]
			== 0 ? D_PAS * env->plane_x : 0);
		env->cam.pos_y +=
			(env->map
			[(int)(env->cam.pos_y + env->plane_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->plane_y : 0);
			act = 1;
	}
	if (env->key[SDL_SCANCODE_A] == 1)
	{
		env->cam.pos_x -=
			(env->map
			[(int)env->cam.pos_y][(int)(env->cam.pos_x - env->plane_x * D_PAS)]
			== 0 ? D_PAS * env->plane_x : 0);
		env->cam.pos_y -=
			(env->map
			[(int)(env->cam.pos_y - env->plane_y * D_PAS)][(int)env->cam.pos_x]
			== 0 ? D_PAS * env->plane_y: 0);
			act = 1;
	}
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
	if (env->key[SDL_SCANCODE_Q] == 1)
		env->w_c = 1;
	if (env->key[SDL_SCANCODE_E] == 1)
		env->w_c = 2;
	if (env->key[SDL_SCANCODE_Z] == 1)
		env->w_c = 3;
	if (env->key[SDL_SCANCODE_C] == 1)
		env->w_c = 4;
	if (env->key[SDL_SCANCODE_T] == 1)
		env->w_c = 0;
	if (env->key[SDL_SCANCODE_F] == 1 && env->lock == 0)
	{
		env->lock = 1;
		print_map(env);
	}
	if (env->key[SDL_SCANCODE_G] == 1)
		env->lock = 0;
	return (act);
}

static int	global_loop(t_env *env)
{
	int		x;
	int		y;
	int		bx;
	int		by;
	while (env->run)
	{
		SDL_PollEvent(&env->event);
		if (SDL_GetMouseState(&x, &y) && (SDL_BUTTON(SDL_BUTTON_LEFT) | SDL_BUTTON(SDL_BUTTON_RIGHT)) && bx != x && by != y)
		{
			bx = x;
			by = y;
	//		printf("%d %d\n", x, y);
			if (env->scree_inf[y][x] != NULL && *env->scree_inf[y][x] != -1)
			{
	//			printf("current map -> %d\n", *env->scree_inf[y][x]);
			if (SDL_BUTTON(SDL_BUTTON_LEFT))
				*env->scree_inf[y][x] = env->w_c;
			}
		}
		if (env->event.type == 256)
			env->run = 0;
		if (env->event.window.type == SDL_WINDOWEVENT_CLOSE
			|| env->event.key.keysym.sym == SDLK_ESCAPE
			|| env->event.type == SDL_QUIT)
				exit (1);
		handle_events(env);
		redraw(env);
		draw_sprite(env, &env->sprite[0]);
		draw_sprite(env, &env->sprite[1]);
		draw_sprite(env, &env->sprite[2]);
		ft_clear_zbuffer(env);
		SDL_UpdateTexture(env->texture, NULL, env->pixels, (int)WIN_W << 2);
		SDL_RenderCopy(env->render, env->texture, NULL, NULL);
		SDL_RenderPresent(env->render);
		env->key = SDL_GetKeyboardState(NULL);
	}
	exit(1);
	return (0);
}

void	init_color(t_env *env)
{
	env->color[0][0] = 0xDEE9ED;
	env->color[0][1] = 0xC6C7CB;
	env->color[0][2] = 0x808387;
	env->color[0][3] = 0x71EBAF;
	env->color[0][4] = 0x42A857;
	env->color[0][5] = 0x332F3B;
}

int		**init_int_ttab(int x, int y, int val)
{
	int		i;
	int		j;
	int		**tab;
	int		*line;

	i = -1;
	j = 0;
	tab = (int **)malloc(sizeof(int *) * x);
	line = (int *)malloc(sizeof(int) * x * y);
	while (++i <= y)
	{
		tab[i] = &line[j];
		j += x;
	}
	i = -1;
	j -= x;
	while (++i < j)
		line[i] = val;
	return (tab);
}

short	**init_short_ttab(int x, int y, int val)
{
	int		i;
	int		j;
	short	**tab;
	short	*line;

	i = -1;
	j = 0;
	tab = (short **)malloc(sizeof(short *) * x);
	line = (short *)malloc(sizeof(short) * x * y);
	while (++i <= y)
	{
		tab[i] = &line[j];
		j += x;
	}
	i = -1;
	j -= x;
	while (++i < j)
		line[i] = val;
	return (tab);
}

void	***init_int_tttab(int x, int y, void *val)
{
	int		i;
	int		j;
	void	**line;
	void	***tab;

	i = -1;
	j = 0;
	tab = (void ***)malloc(sizeof(void **) * x);
	line = (void **)malloc(sizeof(void *) * x * y);
	while (++i <= y)
	{
		tab[i] = &line[j];
		j += x;
	}
	i = -1;
	j -= x;
	while (++i < j)
		line[i] = val;
	return (tab);
}

int		ft_get_block(int color)
{
	if (color == 0xFF6868F8)
		return (3);
	if (color == 0xFFF8F890)
		return (4);
	if (color == 0xFF60F860)
		return (2);
	if (color == 0xFFF84848)
		return (1);
	return (0);
}

short		**parsing_png(SDL_Surface *png, int *h, int *w)
{
	short	**map;
	int		x;
	int		y;

	*h = png->h / 8;
	*w = png->w / 8;
	map = (short **)init_short_ttab(png->w / 8 + 2, png->h / 8 + 2, -1);
	y = 0;
	while (++y <= png->h / 8)
	{
		x = 0;
		while (++x <= png->w / 8)
			map[y][x] = ft_get_block(get_pixel(png, x * 8 + 1 - 8, y * 8 + 1 - 8));
	}
	return (map);
}

void	init_sprite(t_env *env)
{
	env->sprite = (t_sprite *)malloc(sizeof(t_sprite) * 10);
	env->sprite[2] = (t_sprite){env->bmp[SPRITE_TREE], -3, -8};
	env->sprite[0] = (t_sprite){env->bmp[SPRITE_TREE], 9, 9};
	env->sprite[1] = (t_sprite){env->bmp[SPRITE_TREE], 29, 29};
}

int main(int argc, char **argv)
{
	t_env	env;
	int		**map;
	int		*pixels;

	//INIT
	env.cam.pos_x = 8;
	env.cam.pos_y = 16;
	env.dir_x = -8;
	env.dir_y = 0;
	env.plane_x = 0;
	env.plane_y = 5.33f;
	env.run = 1;
	env.pal = 0;
	env.text = 1;
	env.blur = 0;
	env.lock = 0;
	init_color(&env);
	env.zbuffer = init_int_ttab(WIN_W, WIN_H, 42);
	env.scree_inf = (short ***)init_int_tttab(WIN_W, WIN_H, NULL);
	//THREAD INIT
	if (argv[2] && atoi(argv[2]) > 0)
		env.thread_cnt = atoi(argv[2]);
	else
		env.thread_cnt = 1;
	env.args = (t_args *)malloc(sizeof(t_args) * (env.thread_cnt + 1));
	env.thread = malloc_thread(env.thread_cnt, env.args, &env);

	//WIN INIT
	if (SDL_Init(SDL_INIT_EVENTS) == -1)
		exit(2);
	if (IMG_Init(IMG_INIT_PNG) == -1)
		exit(2);
	env.win = SDL_CreateWindow("Wolf3D", 0, 0, WIN_W, WIN_H, 0);
	env.render = SDL_CreateRenderer(env.win, 0,
		SDL_RENDERER_TARGETTEXTURE
		| SDL_RENDERER_SOFTWARE
		| SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC
		);
	SDL_SetRenderDrawColor(env.render, 0xC0, 0, 0, 255);
	SDL_RenderClear(env.render);
	SDL_RenderPresent(env.render);
	env.pixels = (int *)malloc(sizeof(int) * (WIN_H * WIN_W));
	env.texture = SDL_CreateTexture(env.render,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		WIN_W, WIN_H);
	SDL_SetRenderTarget(env.render, env.texture);

	//WOLF INIT
	env.key = SDL_GetKeyboardState(NULL);
	env.bmp = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 6);
	env.wall = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 4);
	env.wall[0] = SDL_ConvertSurfaceFormat(
				IMG_Load("ressources/wall_red.png"),
				SDL_PIXELFORMAT_RGBA8888, 0);
	env.wall[1] = SDL_ConvertSurfaceFormat(
				IMG_Load("ressources/wall_green.png"),
				SDL_PIXELFORMAT_RGBA8888, 0);
	env.wall[2] = SDL_ConvertSurfaceFormat(
				IMG_Load("ressources/wall_blue.png"),
				SDL_PIXELFORMAT_RGBA8888, 0);
	env.wall[3] = SDL_ConvertSurfaceFormat(
				IMG_Load("ressources/wall_yellow.png"),
				SDL_PIXELFORMAT_RGBA8888, 0);
	env.bmp[0] = IMG_Load("ressources/wall_green.png");
	env.bmp[0] = SDL_ConvertSurfaceFormat(env.bmp[0], SDL_PIXELFORMAT_RGBA8888, 0);
	env.bmp[1] = SDL_LoadBMP("ressources/ground.bmp");
	env.bmp[2] = IMG_Load("ressources/floor.png");
	env.bmp[2] = SDL_ConvertSurfaceFormat(env.bmp[2], SDL_PIXELFORMAT_RGBA8888, 0);
	env.bmp[3] = IMG_Load("ressources/grass.png");
	env.bmp[3] = SDL_ConvertSurfaceFormat(env.bmp[3], SDL_PIXELFORMAT_RGBA8888, 0);
	env.bmp[SPRITE_TREE] = SDL_ConvertSurfaceFormat(
				IMG_Load("ressources/tree.png"),
				SDL_PIXELFORMAT_RGBA8888, 0);
	env.bmp[SPRITE_KART] = SDL_ConvertSurfaceFormat(
				IMG_Load("ressources/kart_mario.png"),
				SDL_PIXELFORMAT_RGBA8888, 0);
	init_sprite(&env);
	env.map = (short **)parsing_png(env.bmp[2], &env.map_h, &env.map_w);
//	env.map = parsing(argv[1], &env.map_h, &env.map_w);
	env.skybox = IMG_Load("ressources/skybox1.png");
	env.skybox = SDL_ConvertSurfaceFormat(env.skybox, SDL_PIXELFORMAT_RGBA8888, 0);
    return (global_loop(&env));
}
