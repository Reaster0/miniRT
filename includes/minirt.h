/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:19:26 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/25 11:57:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "../dependencies/libft/libft.h"
# include "shapes.h"
# include "math.h"
# include "get_next_line.h"

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_data		*data;
}				t_vars;

typedef struct	s_all
{
	t_data		*img;
	t_2d		*img_xy;
	t_vars		*vars;
	t_2d		res;
	int			i;
	int			j;
	int			nbr_img;
}				t_all;

float			itof(char *str, int *i);
int				read3d(char *str, t_3d *value, int *i);
float			fix_float(float nbr, float max, float min);
void			fix_3d(t_3d *d3, float min, float max);

void			end_all_life(t_shapes *shapes);
int				refresh(t_all *all);
int				end_of_mlx(t_all *all);
void			fix_screen(t_vars *vars, t_2d *xy);
int				set_startmlx(t_all *all, t_data **img,
				t_shapes *shapes, t_2d *res);
void			set_val_null(t_2d *res, t_shapes *shapes, int *i);
int				key_press(int keycode, t_all *all);

t_camera		*cam_last(t_camera *camera);
t_cylinder		*cy_last(t_cylinder *cylinder);
t_light			*li_last(t_light *light);
t_plane			*pla_last(t_plane *plane);
t_sphere		*sphe_last(t_sphere *sphere);
t_square		*squ_last(t_square *square);
t_triangle		*tri_last(t_triangle *triangle);
t_camera		*id_cam(t_camera *camera, int i);
int				nbr_cam(t_camera *camera);

int				export_bmp(t_shapes *shapes, t_all *all, t_data *img,
				t_vars *vars);
void			skip(int *i, char *str);
int				check_error(char *str);
int				nbr_cam(t_camera *camera);
void			process_fullinter(t_vars *vars, t_data *img, t_all *all,
				t_shapes *shapes);
void			fix_screen(t_vars *vars, t_2d *xy);

void			filter_invert(t_vars *vars, t_data *data, t_2d *xy);
void			filter_psyche(t_vars *vars, t_data *data, t_2d *xy);

int				parsfile(char *path, t_2d *res, int *ambi, t_shapes *shapes);
int				pars_cam(char *str, t_camera **camera);
int				pars_light(char *str, t_light **light);
int				pars_sphere(char *str, t_sphere **sphere);
int				pars_plane(char *str, t_plane **plane);
int				pars_square(char *str, t_square **square);
int				pars_cylinder(char *str, t_cylinder **cylinder);
int				pars_triangle(char *str, t_triangle **triangle);

int				create_trgb(int t, int r, int g, int b);
void			change_r(int *trgb, int r);
void			change_g(int *trgb, int g);
void			change_b(int *trgb, int b);
void			color_up(int *trgb1, int trgb2);

int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				get_opposite(int color);
int				add_shade(double shade, int color);
t_data			new_img(t_vars *vars, int y, int x);
void			img_adress(t_data *data);
void			mlx_pixel_put_fast(t_data *data, int x, int y, int color);
char			*get_pixel(t_data *data, int x, int y);
#endif
