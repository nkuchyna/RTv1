/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_cam_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:45:36 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/13 19:15:04 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_rotate_vector(t_image *img, double *a, double *b, double *c)
{
	double			y;
	double			z;
	double			x1;
	double			z1;

	y = (*b) * cos(img->v_dir[0]) + (*c) * sin(img->v_dir[0]);
	z = (*c) * cos(img->v_dir[0]) - (*b) * sin(img->v_dir[0]);
	x1 = (*a) * cos(img->v_dir[1]) + z * sin(img->v_dir[1]);
	z1 = z * cos(img->v_dir[1]) - (*a) * sin(img->v_dir[1]);
	(*a) = x1 * cos(img->v_dir[2]) - y * sin(img->v_dir[2]);
	(*b) = x1 * sin(img->v_dir[2]) + y * cos(img->v_dir[2]);
	(*c) = z1;
}

void	ft_calc_cam_vector(double x, double y, t_image *img)
{
	double		a;
	double		b;
	double		c;

	a = x * 0.5 / W_SIZE;
	b = y * 0.5 / W_SIZE;
	c = img->zoom;
	ft_rotate_vector(img, &a, &b, &c);
	img->ov = (t_vector){a, b, c};
	img->ov = NORM_VECTOR(img->ov);
}
