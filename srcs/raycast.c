# include "rt.h"

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
	int				real_draw_end;
	int				real_draw_start;
	int				real_dist;
}					t_ray;

t_vector_inc		set_vector_by_x(t_vector_inc vec)
{
	return ((t_vector_inc){
		vec.dx * fabs(1 / vec.dx),
		vec.dy * fabs(1 / vec.dx), 0});
}

t_vector_inc		set_vector_by_y(t_vector_inc vec)
{
	return ((t_vector_inc){
		vec.dx * fabs(1 / vec.dy),
		vec.dy * fabs(1 / vec.dy), 0});
}

void	set_ray(t_env *env, t_ray *ray, int x)
{
	double		correct;

	correct = 1;
	ray->cam_x = 2 * x / (double)WIN_W;
	ray->cam_x -= 1;
//	ray->cam_x *= 8;
//	correct = fabs(ray->cam_x / 32);
	ray->pos_x = env->cam.pos_x;
	ray->pos_y = env->cam.pos_y;
	ray->dir_x = env->dir_x + ray->plane_x * ray->cam_x;
	ray->dir_y = env->dir_y + ray->plane_y * ray->cam_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->delta_dist_x =
		sqrt(1 + (ray->dir_y * ray->dir_y) / (ray->dir_x * ray->dir_x));
	ray->delta_dist_y =
		sqrt(1 + (ray->dir_x * ray->dir_x) / (ray->dir_y * ray->dir_y));
}

void	set_raystep(t_env *env, t_ray *ray)
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

int		is_wall(int i)
{
	if (i == 3)
		return (i);
	else
		return (0);
}

int		launch_ray(t_env *env, t_ray *ray)
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

void	get_wall_inf(t_env *env, t_ray *ray, int x)
{
	if (ray->side == 0)
		ray->wall_dist =
			(ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dist =
			(ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	if ((ray->side == 0 && (ray->pos_x - ray->map_x < 0))
		|| (ray->side == 1 && (ray->pos_y - ray->map_y < 0)))
		ray->nside = 2;
	else
		ray->nside = 0;
	ray->line_height = (int)(256 / ray->wall_dist);
	ray->draw_start = WIN_H / 4;//-ray->line_height / 2 + ((WIN_H / 4));
	ray->draw_end = ray->line_height + ((WIN_H / 4));
	ray->real_draw_end = ray->draw_end;
	ray->real_draw_start = ray->draw_start;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= (int)WIN_H)
		ray->draw_end = (int)WIN_H - 1;
	if (ray->side == 0 || ray->side == 2)
		ray->wallx = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wallx = ray->pos_x + ray->wall_dist * ray->dir_x;
	ray->wallx -= floor(ray->wallx);
}

void	print_wall_uni(t_env *env, t_ray *ray, int x)
{
	int		color;;
	int		i;

	i = ray->draw_start;
	color = env->color[env->pal][ray->side + ray->nside];
	while (i + 10 < ray->draw_end)
	{
		px2img(env->pixels, color, x, i);
		px2img(env->pixels, color, x, i + 1);
		px2img(env->pixels, color, x, i + 2);
		px2img(env->pixels, color, x, i + 3);
		px2img(env->pixels, color, x, i + 4);
		px2img(env->pixels, color, x, i + 5);
		px2img(env->pixels, color, x, i + 6);
		px2img(env->pixels, color, x, i + 7);
		px2img(env->pixels, color, x, i + 8);
		px2img(env->pixels, color, x, i + 9);
		i += 10;
	}
	i--;
	while (++i < ray->draw_end)
		px2img(env->pixels, color, x, i);
}

void	print_roof_uni(t_env *env, t_ray *ray, int x)
{
	int		color;;
	int		i;

	i = 0;
	color = env->color[env->pal][4];
	while (i + 10 < ray->draw_end)
	{
		px2img(env->pixels, color, x, i);
		px2img(env->pixels, color, x, i + 1);
		px2img(env->pixels, color, x, i + 2);
		px2img(env->pixels, color, x, i + 3);
		px2img(env->pixels, color, x, i + 4);
		px2img(env->pixels, color, x, i + 5);
		px2img(env->pixels, color, x, i + 6);
		px2img(env->pixels, color, x, i + 7);
		px2img(env->pixels, color, x, i + 8);
		px2img(env->pixels, color, x, i + 9);
		i += 10;
	}
	i--;
	while (++i < ray->draw_end)
		px2img(env->pixels, color, x, i);
}

void	print_floor_uni(t_env *env, t_ray *ray, int x)
{
	int		color;;
	int		i;

	i = ray->draw_end;
	color = env->color[env->pal][5];
	while (i + 10 < WIN_H - 1)
	{
		px2img(env->pixels, color, x, i);
		px2img(env->pixels, color, x, i + 1);
		px2img(env->pixels, color, x, i + 2);
		px2img(env->pixels, color, x, i + 3);
		px2img(env->pixels, color, x, i + 4);
		px2img(env->pixels, color, x, i + 5);
		px2img(env->pixels, color, x, i + 6);
		px2img(env->pixels, color, x, i + 7);
		px2img(env->pixels, color, x, i + 8);
		px2img(env->pixels, color, x, i + 9);
		i += 10;
	}
	i--;
	while (++i < WIN_H - 1)
		px2img(env->pixels, color, x, i);
}

int		blend(unsigned char *fg, unsigned char *bg)
{
	unsigned int		alpha;
	unsigned int		inv_alpha;
	unsigned char		res[4];

	alpha = fg[3] + 1;
	inv_alpha = 256 - fg[3];
	res[2] = (unsigned char)((alpha * fg[2] + inv_alpha * bg[2]) >> 8);
	res[0] = (unsigned char)((alpha * fg[0] + inv_alpha * bg[0]) >> 8);
	res[1] = (unsigned char)((alpha * fg[1] + inv_alpha * bg[1]) >> 8);
	res[3] = 0xFF;
	return (*(unsigned int *)res);
}

void	print_wall_text(t_env *env, t_ray *ray, int x)
{
	int			textx;
	int			y;
	int			d;
	int			texty;
	int			color;
	int			fg;
	char		alpha;
	SDL_Surface	*text;

	if (ray->hit > 0 && ray->hit <= 4)
		text = env->wall[ray->hit - 1];
	else
		text = env->wall[0];
	textx = (int)(ray->wallx * (double)((text->w))) % text->w;
	if ((ray->side == 0) && ray->dir_x > 0)
		textx = text->w - textx - 1;
	if ((ray->side == 1) && ray->dir_y < 0)
		textx = text->w - textx - 1;
	y = (ray->real_draw_end - ray->real_draw_start) * 3 / 4 + ray->real_draw_start;
	if (env->blur == 1)
	{
		fg = ray->wall_dist * 26;
		if (!(fg < 0xFF))
			fg = 0xFF;
		fg <<= 24;
		fg |= 0x00FFFFFF;
	}
	y--;
	while (++y <= ray->draw_end)
	{
		d = (y << 8) - ((int)WIN_H << 6)
			+ ((int)ray->line_height << 7);
		texty = ((d * text->h) / ray->line_height) / 64;
		texty %= text->h;
		color = get_pixel(text, textx, texty % text->h);
	//	color = blend((void *)&fg, (void *)&color);
	//	color = blend((void *)&color, (void *)&env->pixels[x + y * (int)(WIN_W)]);
		if (env->zbuffer[y][x] > ray->wall_dist)
		{
			env->zbuffer[y][x] = ray->wall_dist;
			px2img(env->pixels, color, x, y);
		}
	}
}

void	set_side(t_ray *ray)
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

void	print_skybox(t_env *env, t_ray *ray, int x)
{
	double	radius;
	int		textx;
	int		y;

	radius = atan2(ray->dir_x, ray->dir_y) + M_PI;
	textx = 1.32 * env->skybox->w * radius / M_PI;
	textx = textx >> 1;
	y = 0;
	while (y <= WIN_H / 4)
	{
		px2img(env->pixels, get_pixel(env->skybox, textx, (y * 1 / 7) % env->skybox->h), x, y);
//		env->zbuffer[y][x] = INT_MAX;
		y++;
	}
}

void	draw_floor_text(t_env *env, t_ray *ray, int x)
{
	int			y;
	int			color;
	int			fg;
	SDL_Surface	*text;
	int			tmp;
	int			hit;
	y = WIN_H / 4;
	ray->dist_player = 0.0f;
	set_side(ray);
	while (++y < WIN_H)
	{
		tmp = 0;
		if (y < ray->draw_end)
			text = env->bmp[3];
		else
			text = env->bmp[2];
		ray->current_dist = (256 + 128) / (y * 2 - WIN_H / 2);
		ray->weight = (ray->current_dist - ray->dist_player)
					/ (ray->wall_dist - ray->dist_player);
		ray->current_floor_x =
			ray->weight * ray->floor_x_wall + (1.0 - ray->weight) * ray->pos_x;
		ray->current_floor_y =
			ray->weight * ray->floor_y_wall + (1.0 - ray->weight) * ray->pos_y;
		if (((int)(ray->current_floor_x) > 0 && (int)ray->current_floor_y > 0)
		&& ((int)ray->current_floor_x <= env->map_w && (int)ray->current_floor_y <= env->map_h)
		&& ((int)ray->current_floor_y >= 0 && (int)ray->current_floor_x >= 0 && (int)ray->current_floor_x <= 256 && (int)ray->current_floor_y <= 256)
		&& env->map[(int)ray->current_floor_y][(int)ray->current_floor_x] != 0)
		{
			hit = env->map[(int)ray->current_floor_y][(int)ray->current_floor_x];
			if (hit > 0 && hit < 5)
				text = env->wall[hit - 1];
			else
				text = env->wall[0];
			tmp = 1;
			ray->floor_text_x =
				abs((int)(ray->current_floor_x * 8 - 8)) % (text->w);
			ray->floor_text_y =
				abs((int)(ray->current_floor_y * 8 - 8)) % (text->h);
		}
		else
		{
			ray->current_dist = 512 / (y * 2 - WIN_H / 2);
			ray->weight = (ray->current_dist - ray->dist_player)
						/ (ray->wall_dist - ray->dist_player);
			ray->current_floor_x =
				ray->weight * ray->floor_x_wall + (1.0 - ray->weight) * ray->pos_x;
			ray->current_floor_y =
				ray->weight * ray->floor_y_wall + (1.0 - ray->weight) * ray->pos_y;

			ray->floor_text_x =
				abs((int)(ray->current_floor_x * 7.999 - 8)) % (text->w);
			ray->floor_text_y =
				abs((int)(ray->current_floor_y * 7.999 - 8)) % (text->h);
		}
		color = get_pixel(text, ray->floor_text_x, ray->floor_text_y);
		if (env->blur == 1)
		{
			fg = ray->current_dist * 26;
			if (!(fg < 0xFF))
				fg = 0xFF;
			fg = (fg << 24) & 0xFF000000;
			fg |= 0x00FFFFFF;
			color = blend((void *)&fg, (void *)&color);
		}
		if (env->zbuffer[y][x] == INT_MAX || tmp == 1)
			px2img(env->pixels, color, x, y - 1);
		if ((int)ray->current_floor_y >= 0 && (int)ray->current_floor_x >= 0 && (int)ray->current_floor_x <= 257 && (int)ray->current_floor_y <= 257)
			env->scree_inf[y][x] = &env->map[(int)ray->current_floor_y][(int)ray->current_floor_x];
		else
			env->scree_inf[y][x] = NULL;
//		env->zbuffer[y][x] = INT_MAX;
	}
}

int		raycast(t_env *env, int start, int end)
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
		get_wall_inf(env, &ray, x);
		print_wall_text(env, &ray, x);
		while (ray.hit != -1 && env->text == 1)
		{
			ray.hit = launch_ray(env, &ray);
			get_wall_inf(env, &ray, x);
			print_wall_text(env, &ray, x);
		}
		if (env->text == 1)
		{
	//		print_wall_text(env, &ray, x);
	//		print_roof_uni(env, &ray, x);
			print_skybox(env, &ray, x);
			draw_floor_text(env, &ray, x);
		}
		else
		{
			print_wall_uni(env, &ray, x);
			print_floor_uni(env, &ray, x);
			print_roof_uni(env, &ray, x);
		}
	}
	return (1);
}
