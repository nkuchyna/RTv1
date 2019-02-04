/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_and_light.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:22:52 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 17:51:34 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_check_color_and_specular(t_object *obj)
{
	if (obj->red < 0)
		obj->red *= -1;
	if (obj->green < 0)
		obj->green *= -1;
	if (obj->blue < 0)
		obj->blue *= -1;
	if (obj->red > 255)
		obj->red = 255;
	if (obj->green > 255)
		obj->green = 255;
	if (obj->blue > 255)
		obj->blue = 255;
	if (obj->specular > 1000)
		obj->specular = 1000;
}

void		ft_check_lights(t_light *lights, int light_nbr)
{
	int		k;
	double	sum_i;

	k = 0;
	sum_i = 0;
	while (k < light_nbr)
	{
		if (lights[k].i < 0)
			lights[k].i *= -1;
		sum_i += lights[k].i;
		k++;
	}
	k = 0;
	if (sum_i > 1)
		while (k < light_nbr)
		{
			lights[k].i = lights[k].i / sum_i;
			k++;
		}
}
