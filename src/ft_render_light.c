/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:23:10 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 15:56:43 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_calc_nonspec_obj(t_vector n, double len_n, t_image *img)
{
	int			k;
	double		lim_param;
	double		sum_i;
	t_vector	l;
	t_vector	l2;

	k = 0;
	sum_i = 0;
	while (k < img->light_nbr)
	{
		img->intersection = 0;
		l = img->lights[k].position - img->p;
		ft_obj_inter(img, l, img->p, 1);
		l = NORM_VECTOR(l);
		if (img->intersection == 0)
		{
			lim_param = SVM(n, l);
			if (lim_param > 0)
				sum_i += img->lights[k].i * lim_param / (len_n * LEN_VECTOR(l));
		}
		k++;
	}
	return (sum_i);
}

double	ft_calc_spec_obj(t_vector n, double len_n, t_image *img, double spec)
{
	int			k;
	double		lim_param;
	double		sum_i_s;
	t_vector	r;
	t_vector	l;

	k = 0;
	sum_i_s = 0;
	while (k < img->light_nbr)
	{
		l = img->lights[k].position - img->p;
		ft_obj_inter(img, l, img->p, 1);
		l = NORM_VECTOR(l);
		if (img->intersection == 0)
		{
			img->intersection = 0;
			r = SCALE_VECTOR(2 * SVM(n, l), n) - l;
			lim_param = SVM(r, -img->ov);
			if (lim_param > 0)
				sum_i_s += img->lights[k].i * pow(lim_param / (LEN_VECTOR(r)
				* LEN_VECTOR(-img->ov)), spec);
		}
		k++;
	}
	return (sum_i_s);
}

void	ft_render_light(t_object *obj, t_image *img)
{
	t_vector	n;
	t_vector	a;
	t_vector	r;
	double		len_n;
	double		sum_i;

	img->intersection = 0;
	img->shadows = 1;
	img->sum_i = 0;
	img->sum_i_s = 0;
	if (obj->type == 2 || obj->type == 3 || obj->type == 4)
		n = obj->n;
	else
	{
		img->p = img->cam + SCALE_VECTOR(img->t_min, img->ov);
		a = img->p - obj->c;
		n = NORM_VECTOR(a);
	}
	len_n = LEN_VECTOR(n);
	img->sum_i = ft_calc_nonspec_obj(n, len_n, img);
	if (obj->specular > 0 && img->intersection == 0)
	{
		img->intersection = 0;
		img->sum_i_s = ft_calc_spec_obj(n, len_n, img, obj->specular);
	}
}
