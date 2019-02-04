/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:55:07 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 15:50:16 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_sphere(t_object *obj, t_image *img, t_vector ov, t_vector o)
{
	t_vector	oc;
	double		k1;
	double		k2;
	double		k3;

	oc = o - obj->c;
	k1 = SVM(ov, ov);
	k2 = 2 * SVM(oc, ov);
	k3 = SVM(oc, oc) - obj->radius * obj->radius;
	obj->t1 = -1;
	obj->t2 = -1;
	if ((obj->des = k2 * k2 - 4 * k1 * k3) >= 0)
	{
		obj->t1 = (-k2 + sqrt(obj->des)) / (2 * k1);
		obj->t2 = (-k2 - sqrt(obj->des)) / (2 * k1);
	}
	ft_define_t_min(img, obj);
}

void	ft_plane(t_object *obj, t_image *img, t_vector ov, t_vector o)
{
	t_vector	oc;
	double		k1;
	double		k2;
	double		koef;

	oc = o - obj->c;
	koef = 1;
	obj->t1 = -1;
	if ((k1 = SVM(ov, obj->dir)) == 0)
		return ;
	k2 = SVM(oc, obj->dir);
	if (k1 == k2)
		koef = -1;
	obj->t1 = -k2 / k1 * koef;
	if (k1 > 0)
		obj->n = -obj->dir;
	else
		obj->n = obj->dir;
	ft_define_t_min(img, obj);
}

void	ft_cylind(t_object *obj, t_image *img, t_vector ov, t_vector o)
{
	t_vector	oc;
	double		k1;
	double		k2;
	double		k3;

	oc = o - obj->c;
	k1 = SVM(ov, ov) - pow(SVM(ov, obj->dir), 2);
	k2 = 2 * (SVM(ov, oc) - SVM(ov, obj->dir) * SVM(oc, obj->dir));
	k3 = SVM(oc, oc) - pow(SVM(oc, obj->dir), 2) - obj->radius * obj->radius;
	obj->t1 = -1;
	obj->t2 = -1;
	if ((obj->des = k2 * k2 - 4 * k1 * k3) >= 0)
	{
		obj->t1 = (-k2 + sqrt(obj->des)) / (2 * k1);
		obj->t2 = (-k2 - sqrt(obj->des)) / (2 * k1);
	}
	ft_define_t_min(img, obj);
}

void	ft_cone(t_object *obj, t_image *img, t_vector ov, t_vector o)
{
	t_vector	oc;
	double		k1;
	double		k2;
	double		k3;
	double		k;

	oc = o - obj->c;
	k = (1 + obj->tan_ha * obj->tan_ha);
	k1 = SVM(ov, ov) - k * pow(SVM(ov, obj->dir), 2);
	k2 = 2 * (SVM(ov, oc) - k * SVM(ov, obj->dir) * SVM(oc, obj->dir));
	k3 = SVM(oc, oc) - k * pow(SVM(oc, obj->dir), 2);
	obj->t1 = -1;
	obj->t2 = -1;
	if ((obj->des = k2 * k2 - 4 * k1 * k3) >= 0)
	{
		obj->t1 = (-k2 + sqrt(obj->des)) / (2 * k1);
		obj->t2 = (-k2 - sqrt(obj->des)) / (2 * k1);
	}
	ft_define_t_min(img, obj);
}
