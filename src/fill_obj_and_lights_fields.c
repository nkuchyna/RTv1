/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj_and_lights_fields.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 22:03:36 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/02 14:36:00 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_fill_param_field(double *param, char *line)
{
	char	**fields;
	int		k;
	int		j;

	k = 0;
	j = 0;
	fields = ft_strsplit(line, ' ');
	while (fields[k] != NULL)
	{
		if (ft_check_nbr(fields[k], &j) == 1)
			*param = ft_atof(fields[k]);
		k++;
	}
	ft_free_char_array(fields);
}

void		ft_fill_color_field(t_object *obj, char *line)
{
	t_vector color;

	color = (t_vector){0, 0, 0};
	ft_fill_vector_fields(&color, line);
	obj->red = color[0];
	obj->green = color[1];
	obj->blue = color[2];
}

void		ft_define_obj_type(t_object *obj, char *line)
{
	if (ft_strstr_new(line, "sphere") == 1)
		obj->type = 1;
	if (ft_strstr_new(line, "plane") == 1)
		obj->type = 2;
	if (ft_strstr_new(line, "cylinder") == 1)
		obj->type = 3;
	if (ft_strstr_new(line, "cone") == 1)
		obj->type = 4;
}

void		ft_fill_obj_f(t_object *obj, char **line, int fd, int *k_obj)
{
	int		ret;

	ret = 0;
	obj->index = ++(*k_obj);
	ft_define_obj_type(obj, *line);
	free(*line);
	while ((ret = get_next_line(fd, &(*line)) == 1) && ft_find_obj(*line) != 1)
	{
		if (ft_strstr_new(*line, "radius") == 1)
			ft_fill_param_field(&obj->radius, *line);
		if (ft_strstr_new(*line, "center") == 1)
			ft_fill_vector_fields(&obj->c, *line);
		if (ft_strstr_new(*line, "direction") == 1)
			ft_fill_vector_fields(&obj->dir, *line);
		if (ft_strstr_new(*line, "specular") == 1)
			ft_fill_param_field(&obj->specular, *line);
		if (ft_strstr_new(*line, "color") == 1)
			ft_fill_color_field(obj, *line);
		if (ft_strstr_new(*line, "ang") == 1)
			ft_fill_param_field(&obj->cone_ang, *line);
		ft_strdel(&(*line));
	}
}

void		ft_fill_light_fealds(t_light *light, char *line, int fd)
{
	ft_fill_vector_fields(&light->position, line);
	ft_fill_param_field(&light->i, line);
}
