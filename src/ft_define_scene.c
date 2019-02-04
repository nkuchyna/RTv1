/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:35:38 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 12:58:38 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_find_obj(char *line)
{
	if ((ft_strstr_new(line, "sphere") == 1)
	|| (ft_strstr_new(line, "plane") == 1)
	|| (ft_strstr_new(line, "cone") == 1)
	|| (ft_strstr_new(line, "cylinder") == 1))
		return (1);
	return (0);
}

static int	ft_count_scene_el(char *s, int *obj_nbr, int *light_nbr, int *cam)
{
	int		fd;
	char	*line;

	line = NULL;
	if ((fd = open(s, O_RDWR)) < 0)
	{
		ft_putstr(strerror(errno));
		ft_putstr("\nusage: ./RTv1 [scene]\n");
		return (1);
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_find_obj(line) == 1)
			(*obj_nbr)++;
		if (ft_strstr_new(line, "spot_light") == 1)
			(*light_nbr)++;
		if (ft_strstr_new(line, "camera") == 1)
			(*cam)++;
		free(line);
	}
	close(fd);
	return (0);
}

static int	ft_add_inf(t_image *img, char *argv)
{
	int		fd;
	int		k_obj;
	int		k_light;
	char	*line;

	k_obj = 0;
	k_light = 0;
	if ((fd = open(argv, O_RDWR)) < 0)
		return (1);
	ft_add_default_obj_params(img->objects, img->obj_nbr);
	ft_add_default_light_params(img->lights, img->light_nbr);
	ft_add_default_camera_params(img);
	while (get_next_line(fd, &line) == 1)
	{
		while (ft_find_obj(line) == 1)
			ft_fill_obj_f(&img->objects[k_obj], &line, fd, &k_obj);
		if (ft_strstr_new(line, "spot_light") == 1)
			ft_fill_light_fealds(&img->lights[k_light++], line, fd);
		if (ft_strstr_new(line, "camera") == 1)
			ft_fill_vector_fields(&img->cam, line);
		if (ft_strstr_new(line, "view_direction") == 1)
			ft_fill_vector_fields(&img->v_dir, line);
		ft_strdel(&line);
	}
	return (0);
}

int			ft_define_scene(char *argv, t_image *img)
{
	int		fd;
	char	*line;
	int		obj_nbr;
	int		light_nbr;
	int		cam;

	obj_nbr = 0;
	light_nbr = 0;
	cam = 0;
	if (ft_count_scene_el(argv, &obj_nbr, &light_nbr, &cam) == 1
	|| obj_nbr == 0 || cam != 1 || light_nbr == 0)
	{
		ft_putstr("Must be one camera and at least one object and light.\n");
		return (1);
	}
	img->obj_nbr = obj_nbr;
	img->light_nbr = light_nbr;
	img->win_preview_size = 1;
	img->zoom = 1;
	if (!(img->objects = (t_object*)malloc(sizeof(t_object) * obj_nbr)))
		return (1);
	if (!(img->lights = (t_light*)malloc(sizeof(t_light) * light_nbr)))
		return (1);
	ft_add_inf(img, argv);
	return (0);
}
