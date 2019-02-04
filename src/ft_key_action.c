/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 17:58:11 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 18:07:37 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_key_action(int key, t_window *win)
{
	t_image		*img;

	img = win->img;
	if (key == 53)
	{
		ft_exit(win);
		return (0);
	}
	return (0);
}
