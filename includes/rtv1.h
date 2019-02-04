/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:53:20 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 18:04:51 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define W_SIZE 1000
# define SCALE_VECTOR(k, v)	(v * (t_vector){k, k, k})
# define SVM(v1, v2) (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])
# define LEN_VECTOR(v) (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]))
# define NORM_VECTOR(v) (SCALE_VECTOR((1 / LEN_VECTOR(v)), v))

# include <string.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef double	t_vector __attribute__((vector_size(sizeof(double)*3)));

typedef struct	s_object
{
	int			index;
	int			type;
	double		radius;
	double		red;
	double		green;
	double		blue;
	double		specular;
	double		t1;
	double		t2;
	double		des;
	double		tan_ha;
	double		cone_ang;
	t_vector	c;
	t_vector	n;
	t_vector	oc;
	t_vector	dir;
}				t_object;

typedef struct	s_light
{
	double		i;
	t_vector	position;
}				t_light;

typedef struct	s_image
{
	void		*img_ptr;
	char		*img_str;
	int			bpp;
	int			bpl;
	int			end;
	int			obj_nbr;
	int			light_nbr;
	int			obj_index;
	int			shadows;
	int			intersection;
	double		zoom;
	double		win_preview_size;
	double		sum_i;
	double		sum_i_s;
	double		t_min;
	double		max;
	double		min;
	t_vector	cam;
	t_vector	p;
	t_vector	ov;
	t_vector	v_dir;
	t_light		*lights;
	t_object	*objects;
}				t_image;

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		*img;
}				t_window;

void			ft_pretrace_img(t_image *img);
void			ft_obj_inter(t_image *img, t_vector ov, t_vector p, double max);
void			ft_render_light(t_object *obj, t_image *img);
int				ft_define_scene(char *argv, t_image *img);
void			ft_fill_obj_f(t_object *obj, char **line, int fd, int *k_obj);
void			ft_fill_light_fealds(t_light *light, char *line, int fd);
void			ft_fill_vector_fields(t_vector *vector, char *line);
int				ft_check_nbr(char *str, int *j);
double			ft_atof(char *str);
int				ft_strstr_new(char *big, char *lit);
int				ft_find_obj(char *line);
void			ft_add_default_obj_params(t_object *objects, int obj_nbr);
void			ft_add_default_light_params(t_light *lights, int light_nbr);
void			ft_add_default_camera_params(t_image *img);
void			ft_rotate_vector(t_image *img, double *a, double *b, double *c);
void			ft_calc_cam_vector(double x, double y, t_image *img);
void			ft_sphere(t_object *obj, t_image *img, t_vector ov, t_vector o);
void			ft_plane(t_object *obj, t_image *img, t_vector ov, t_vector o);
void			ft_cylind(t_object *obj, t_image *img, t_vector ov, t_vector o);
void			ft_cone(t_object *obj, t_image *img, t_vector ov, t_vector o);
void			ft_define_t_min(t_image *img, t_object *obj);
void			ft_check_color_and_specular(t_object *obj);
void			ft_check_lights(t_light *lights, int light_nbr);
int				ft_key_action(int key, t_window *win);
void			ft_exit(t_window *win);

#endif
