# include "rt.h"
#define FOV 120.0f
#define DIV_FOV 60.0f

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
	ray->cam_x = 2 * x / (double)WIN_W - 1;
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
}

void	print_wall_uni(t_env *env, t_ray *ray, int x)
{
	char	*col;

	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= (int)WIN_H)
		ray->draw_end = (int)WIN_H - 1;
	col = (char *)&env->color[env->pal][ray->side];
	SDL_SetRenderDrawColor(env->render,
		col[0], col[1], col[2], SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(env->render, x, ray->draw_start, x, ray->draw_end);
	col = (char *)&env->color[env->pal][4];
	SDL_SetRenderDrawColor(env->render,
		col[0], col[1], col[2], SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(env->render, x, ray->draw_end, x, WIN_H - 1);
	col = (char *)&env->color[env->pal][5];
	SDL_SetRenderDrawColor(env->render,
		col[0], col[1], col[2], SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(env->render, x, 0, x, ray->draw_start);
}

void	print_wall_text(t_env *env, t_ray *ray, int x)
{
}

int		raycast(t_env *env)
{
	t_ray	ray;
	int		x;
	int		i;

	ray.plane_x = env->plane_x;
	ray.plane_y = env->plane_y;
	x = -1;
	while (++x < WIN_W)
	{
		set_ray(env, &ray, x);
		set_raystep(env, &ray);
		ray.hit = launch_ray(env, &ray);
		get_wall_inf(env, &ray);
		if (ray.hit != 1 && env->text == 1)
			print_wall_text(env, &ray, x);
		else
			print_wall_uni(env, &ray, x);
	}
}
