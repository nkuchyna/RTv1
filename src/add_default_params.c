/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_default_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:17:38 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/02 12:33:44 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_add_default_obj_params(t_object *objects, int obj_nbr)
{
	int		k;

	k = 0;
	while (k < obj_nbr)
	{
		objects[k].index = k + 1;
		objects[k].type = 0;
		objects[k].radius = 0;
		objects[k].c = (t_vector){1, 1, 10};
		objects[k].n = (t_vector){0, 0, 0};
		objects[k].oc = (t_vector){0, 0, 0};
		objects[k].dir = (t_vector){0, 1, 0};
		objects[k].red = 130;
		objects[k].green = 200;
		objects[k].blue = 200;
		objects[k].specular = -1;
		objects[k].cone_ang = 0.5;
		k++;
	}
}

void	ft_add_default_light_params(t_light *lights, int light_nbr)
{
	int		k;

	k = 0;
	while (k < light_nbr)
	{
		lights[k].position = (t_vector){0, 0, 0};
		lights[k].i = 0;
		k++;
	}
}

void	ft_add_default_camera_params(t_image *img)
{
	img->cam = (t_vector){0, 0, -5};
	img->v_dir = (t_vector){0, 0, 0};
}
