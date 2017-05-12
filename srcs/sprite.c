/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:13:29 by gmonein           #+#    #+#             */
/*   Updated: 2017/05/12 18:45:57 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

typedef struct		s_sprite_inf
{
	int			i;
	int			y;
	int			d;
	int			color;
	int			pix;;
	double		sprite_dist;
	double		sprite_x;
	double		sprite_y;

	double		invdet;
	double		transform_x;
	double		transform_y;

	int			sprite_screen_x;

	int			sprite_height;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			draw_start_y;
	int			draw_end_y;
	int			text_x;
	int			text_y;
}				t_sprite_inf;

void	calc_sprite_inf(t_env *env, t_sprite *inf, t_sprite_inf *s)
{
	s->sprite_dist = ((env->cam.pos_x - inf->pos_x) * (env->cam.pos_x - inf->pos_x)
				+ (env->cam.pos_y - inf->pos_y) * (env->cam.pos_y - inf->pos_y));
	s->sprite_dist = ((env->cam.pos_x - inf->pos_x) * (env->cam.pos_x - inf->pos_x)
				+ (env->cam.pos_y - inf->pos_y) * (env->cam.pos_y - inf->pos_y));
	s->sprite_x = inf->pos_x - env->cam.pos_x;
	s->sprite_y = inf->pos_y - env->cam.pos_y;
	s->invdet = 1.0 / (env->dir_y * env->plane_x - env->dir_x * env->plane_y);
	s->transform_x = s->invdet * (env->dir_y * s->sprite_x - env->dir_x * s->sprite_y);
	s->transform_y = s->invdet * (-env->plane_y * s->sprite_x + env->plane_x * s->sprite_y);
	s->sprite_screen_x = (int)((WIN_W / 2) * (1 + s->transform_x / s->transform_y));
	s->sprite_height = abs((int)round((WIN_H / s->transform_y)));
	s->draw_start_y = -s->sprite_height / 2 + WIN_H / 4 - 5;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + WIN_H / 4 - 5;
	if (s->draw_end_y >= WIN_H)
		s->draw_end_y = WIN_H - 1;
	s->sprite_width = abs((int)round((inf->img->w * 3 / s->transform_y)));
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x >= WIN_W)
		s->draw_end_x = WIN_W - 1;
}

void	draw_sprite(t_env *env, t_sprite *inf)
{
	t_sprite_inf s;

	calc_sprite_inf(env, inf, &s);
	inf->sprite_dist =
	((env->cam.pos_x - inf->pos_x) * (env->cam.pos_x - inf->pos_x) + (env->cam.pos_y - inf->pos_y) * (env->cam.pos_y - inf->pos_y));
	s.i = s.draw_start_x - 1;
	while (++s.i < s.draw_end_x)
	{
		s.text_x = (int)(256 * (s.i - (-s.sprite_width / 2 + s.sprite_screen_x))
								* inf->img->w / s.sprite_width) / 256;
		if (s.text_x > inf->img->w)
			s.text_x = inf->img->w - s.text_x;
		s.y = s.draw_start_y - 1;
		if (s.transform_y > 0 && s.i > 0 && s.i < WIN_W)
			while (++s.y < s.draw_end_y)
			{
				s.d = s.y * 256 - (WIN_H * 64 - 5 * 256) + s.sprite_height * 128;
				s.text_y = ((s.d * inf->img->h) / s.sprite_height) / 256;
				s.color = get_pixel(inf->img, s.text_x, s.text_y);
				s.color = blend((void *)&s.color, (void *)&env->pixels[s.i + s.y * (int)(WIN_W)]);
				if (env->zbuffer[s.y][s.i] > inf->sprite_dist)
				{
					if ((get_pixel(inf->img, s.text_x, s.text_y) & 0xFF000000) == 0xFF000000)
						env->zbuffer[s.y][s.i] = inf->sprite_dist;
					px2img(env->pixels, s.color, s.i, s.y);
				}
			}
	}
}
