/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pretrace_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:05:35 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/13 19:09:21 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	ft_define_color(double color, t_image *img, t_object *obj)
{
	double			temp_c;
	double			spec_c;

	spec_c = 0;
	if (obj->specular > 0)
		spec_c = img->sum_i_s * 180;
	temp_c = (color + spec_c) * img->sum_i;
	if (temp_c < 0)
		temp_c = 0;
	if (temp_c > 255)
		temp_c = 255;
	return (temp_c);
}

static void		ft_build_point(t_object *obj, t_image *img, int x, int y)
{
	int			i;
	int			temp;

	temp = 0;
	if (x >= 0 && x < 1000 && y >= 0 && y < 1000)
	{
		i = y * img->bpl + x * 4;
		img->img_str[i] = ft_define_color(obj->blue, img, obj);
		img->img_str[++i] = ft_define_color(obj->green, img, obj);
		img->img_str[++i] = ft_define_color(obj->red, img, obj);
	}
}

static void		ft_reset_params(t_image *img)
{
	img->obj_index = 0;
	img->shadows = 0;
	img->intersection = 0;
}

void			ft_pretrace_img(t_image *img)
{
	double			x;
	double			y;
	t_object		*objects;

	x = -W_SIZE / 2;
	y = -W_SIZE / 2;
	objects = img->objects;
	while (y <= W_SIZE / 2)
	{
		x = -W_SIZE / 2;
		while (x <= W_SIZE / 2)
		{
			ft_reset_params(img);
			ft_calc_cam_vector(x, y, img);
			ft_obj_inter(img, img->ov, img->cam, 1000);
			if (img->obj_index > 0)
			{
				ft_render_light(&objects[img->obj_index - 1], img);
				ft_build_point(&objects[img->obj_index - 1],
				img, x + W_SIZE / 2, -y + W_SIZE / 2);
			}
			x++;
		}
		y++;
	}
}
