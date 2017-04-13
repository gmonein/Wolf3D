# include "rt.h"
#define FOV 120.0f
#define DIV_FOV 60.0f

typedef struct		s_pos
{
	float			x;
	float			y;
}					t_pos;

typedef struct		s_vector_inc
{
	float			dx;
	float			dy;
	float			dif;
}					t_vector_inc;

typedef struct		s_ray
{
	float			cam_x;
	float			pos_x;
	float			pos_y;
	float			map_x;
	float			map_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			side_x;
	float			side_y;
	float			wall_dist;
	float			step_x;
	float			step_y;
	float			delta_dist_x;
	float			delta_dist_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
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
	ray->cam_x = 2 * x / (float)WIN_W - 1;
	ray->pos_x = env->cam.pos_x;
	ray->pos_y = env->cam.pos_y;
	ray->dir_x = env->dir_x + ray->plane_x * ray->cam_x;
	ray->dir_y = env->dir_y + ray->plane_y * ray->cam_x;
	if (x == (int)WIN_W >> 1)
	{
		env->mid_dir_x = ray->dir_x;
		env->mid_dir_y = ray->dir_y;
	}
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

void	get_wall_inf(t_env *env, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist =
			(ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dist =
			(ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->side == 0 && ray->pos_x - ray->map_x < 0
		|| ray->side == 1 && ray->pos_y - ray->map_y < 0)
		ray->side += 2;
	ray->line_height = (int)(WIN_H / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + (int)WIN_H / 2;
	ray->draw_end = ray->line_height / 2 + (int)WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= (int)WIN_H)
		ray->draw_end = (int)WIN_H - 1;
}

void	print_wall_uni(t_env *env, t_ray *ray, int x)
{
	char	*col;

	col = (char *)&env->color[env->pal][ray->side];
	SDL_SetRenderDrawColor(env->render,
		col[0], col[1], col[2], SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(env->render, x, ray->draw_start, x, ray->draw_end);
}

void	print_wall_text(t_env *env, t_ray *ray, int x)
{
	float		wallx;
	int			textx;
	int			y;
	int			d;
	int			texty;
	int			color;

	if (ray->side == 0 || ray->side == 2)
		wallx = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		wallx = ray->pos_x + ray->wall_dist * ray->dir_x;
	wallx -= floor(wallx);
	textx = (int)(wallx * (float)(env->bmp->w));
	if ((ray->side == 0 || ray->side == 2) && ray->dir_x > 0)
		textx = env->bmp->w - textx - 1;
	if ((ray->side == 1 || ray->side == 3) && ray->dir_y < 0)
		textx = env->bmp->w - textx - 1;
	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		d = (y << 8) - ((int)WIN_H << 7)
			+ ((int)ray->line_height << 7);
		texty = ((d * env->bmp->h) / ray->line_height) / 256;
		color = get_pixel(env->bmp, textx, texty);
		if (ray->side & 1 == 1)
			color = (color >> 1) & 8355711;
		px2img(env->pixels, color, x, y);
	}
}

void	draw_floor(t_env *env, t_ray *ray, int x)
{
	int		y;

	y = -1;
	while (++y < ray->draw_start)
		px2img(env->pixels, 0x00A0A0A0, x, y);
}

void	draw_sol(t_env *env, t_ray *ray, int x)
{
	int		y;

	y = ray->draw_end - 1;
	while (++y < WIN_H)
		px2img(env->pixels, 0x00A0A0A0, x, y);
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
		get_wall_inf(env, &ray);
//		if (ray.hit == 2 && env->text == 1)
		print_wall_text(env, &ray, x);
//		else
//			px2img(env->pixels, 0x00FF0000, x, 100);
//			print_wall_uni(env, &ray, x);
		draw_floor(env, &ray, x);
		draw_sol(env, &ray, x);
	}
}
