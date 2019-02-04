/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:49:17 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 18:21:31 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_window	*ft_create_win(void)
{
	void		*mlx_ptr;
	t_window	*win;

	if (!(mlx_ptr = mlx_init()))
		return (NULL);
	if (!(win = (t_window*)malloc(sizeof(t_window) * 1)))
		return (NULL);
	win->mlx_ptr = mlx_ptr;
	if (!(win->win_ptr = mlx_new_window(win->mlx_ptr, W_SIZE,
						W_SIZE, "RTv1")))
		return (NULL);
	return (win);
}

static t_image	*ft_create_img(t_window *win)
{
	t_image		*img;

	if (!(img = (t_image*)malloc(sizeof(t_image) * 1)))
		return (NULL);
	if (!(img->img_ptr = mlx_new_image(win->mlx_ptr, W_SIZE, W_SIZE)))
		return (NULL);
	if (!(img->img_str = mlx_get_data_addr(img->img_ptr, &img->bpp,
						&img->bpl, &img->end)))
		return (NULL);
	win->img = img;
	return (img);
}

void			ft_exit(t_window *win)
{
	mlx_destroy_image(win->mlx_ptr, win->img->img_ptr);
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	exit(1);
}

static void		ft_precalc_init_data(t_image *img)
{
	t_object	*objects;
	t_light		*lights;
	int			k;

	k = 0;
	objects = img->objects;
	lights = img->lights;
	while (k < img->obj_nbr)
	{
		objects[k].oc = img->cam - objects[k].c;
		objects[k].dir = NORM_VECTOR(objects[k].dir);
		ft_check_color_and_specular(&objects[k]);
		if (objects[k].type == 4)
		{
			if (objects[k].cone_ang < -2.5 || objects[k].cone_ang > 2.5)
				objects[k].cone_ang = 2.5;
			objects[k].tan_ha = tan(objects[k].cone_ang / 2);
		}
		k++;
	}
	ft_check_lights(lights, img->light_nbr);
}

int				main(int argc, char **argv)
{
	t_window	*win;
	t_image		*img;

	if (argc != 2)
	{
		ft_putendl("usage: ./RTv1 [scene]");
		return (1);
	}
	if (!(win = ft_create_win()))
		return (1);
	if (!(img = ft_create_img(win)))
		return (1);
	if (ft_define_scene(argv[1], img) == 1)
	{
		ft_exit(win);
		return (1);
	}
	ft_precalc_init_data(img);
	ft_pretrace_img(img);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, 0, 0);
	mlx_hook(win->win_ptr, 17, 1L << 17, ft_exit_x, win);
	mlx_hook(win->win_ptr, 2, 5, &ft_key_action, win);
	mlx_loop(win->mlx_ptr);
	return (0);
}
