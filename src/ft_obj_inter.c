/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:50:44 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 15:56:48 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_define_normal(double t_min, t_object *obj, t_image *img)
{
	double		m;
	double		k;
	t_vector	ca;
	double		cone_r;

	if (obj->type == 3)
	{
		m = SVM(img->ov, obj->dir) * t_min + SVM(obj->oc, obj->dir);
		obj->n = img->p - obj->c - SCALE_VECTOR(m, obj->dir);
		obj->n = NORM_VECTOR(obj->n);
	}
	if (obj->type == 4)
	{
		m = SVM(img->ov, obj->dir) * t_min + SVM(obj->oc, obj->dir);
		ca = obj->c + SCALE_VECTOR(m, obj->dir) - obj->c;
		cone_r = LEN_VECTOR(ca) * tan(obj->cone_ang / 2);
		k = cone_r / m;
		obj->n = img->p - obj->c - SCALE_VECTOR((1 + k * k) * m, obj->dir);
		obj->n = NORM_VECTOR(obj->n);
	}
}

void	ft_define_t_min(t_image *img, t_object *obj)
{
	double		t_min;

	if (obj->des < 0 || obj->t1 < img->min || obj->t1 >= img->max)
		obj->t1 = -1;
	if (obj->des < 0 || obj->t2 < img->min || obj->t2 >= img->max)
		obj->t2 = -1;
	if (obj->t2 < obj->t1 && obj->type != 2 && obj->t2 != -1)
		t_min = obj->t2;
	else
		t_min = obj->t1;
	if (img->shadows == 0 && t_min < img->t_min && t_min != -1)
	{
		img->t_min = t_min;
		img->obj_index = obj->index;
		img->p = img->cam + SCALE_VECTOR(img->t_min, img->ov);
		if (obj->type == 3 || obj->type == 4)
			ft_define_normal(t_min, obj, img);
	}
	if (img->shadows == 1 && t_min < img->t_min && t_min != -1)
		img->intersection = 1;
}

void	ft_obj_inter(t_image *img, t_vector ov, t_vector p, double max)
{
	int			k;
	t_object	*objects;
	t_vector	point;

	k = 0;
	objects = img->objects;
	img->max = max;
	img->min = 0.001;
	img->t_min = 1000;
	while (k < img->obj_nbr)
	{
		if (objects[k].type == 1)
			ft_sphere(&objects[k], img, ov, p);
		if (objects[k].type == 2)
			ft_plane(&objects[k], img, ov, p);
		if (objects[k].type == 3)
			ft_cylind(&objects[k], img, ov, p);
		if (objects[k].type == 4)
			ft_cone(&objects[k], img, ov, p);
		k++;
	}
}
