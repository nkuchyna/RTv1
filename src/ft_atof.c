/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:32:59 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/30 18:28:45 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_define_double_nbr(char *str, int i, double k)
{
	double		integer;
	double		fract;
	double		count;
	double		nbr;

	integer = 0;
	fract = 0;
	count = 0;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
		integer = integer * 10 + (str[i++] - '0');
	if (str[i++] == '.')
		while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0' && count < 6)
		{
			fract = fract * 10 + (str[i++] - '0');
			count++;
		}
	nbr = integer + fract / (pow(10, count));
	return (nbr * k);
}

double		ft_atof(char *str)
{
	int			i;
	double		k;
	double		nbr;

	i = 0;
	k = 1;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
			i++;
		if (str[i] == '-')
			k = -1;
		if (str[i] == '-' || str[i] == '+')
			i++;
		nbr = ft_define_double_nbr(str, i, k);
		return (nbr);
	}
	return (0);
}
