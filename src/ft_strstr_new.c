/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:44:39 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/31 13:44:51 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_strstr_new(char *big, char *lit)
{
	int			i;
	int			k;
	int			a;

	i = 0;
	a = 0;
	k = 0;
	if (ft_strlen(lit) == 0 || !big)
		return (0);
	while (big[i] != '\0' && lit[k] != '\0')
	{
		if (lit[k] == big[i] || lit[k] == big[i] + 32)
		{
			i++;
			k++;
		}
		else
		{
			k = 0;
			i = ++a;
		}
	}
	if (k == ft_strlen(lit))
		return (1);
	return (0);
}
