/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_vector_fields.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:42:48 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/03 13:49:36 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_check_nbr(char *str, int *i)
{
	long int		nbr;
	int				len;
	int				dot_nbr;

	len = 0;
	dot_nbr = 0;
	while (str[*i] == '-' || str[*i] == ',')
		(*i)++;
	while (str[*i] != ',' && str[*i] != '\0' && str[*i] != '}')
	{
		if (!((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.'))
			return (0);
		if (str[*i] == '.')
			dot_nbr++;
		len++;
		(*i)++;
	}
	if (len > 16 || dot_nbr > 1)
		return (0);
	nbr = ft_atoi(str);
	if (!(nbr >= -2147483648 && nbr <= 2147483647))
		return (0);
	return (1);
}

static int	ft_count_elems(char *s, char c)
{
	int		nb;

	nb = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
			s++;
		if (*s == c || (*s == '\0' && *(s - 1) != c))
			nb++;
	}
	return (nb);
}

static void	ft_add_vector_comp(char *str, t_vector *vector)
{
	char		**vect_comp;
	int			k;

	if (ft_count_elems(str, ',') != 3)
	{
		(*vector) = (t_vector){1000, 1000, 1000};
		ft_putstr("WARNING: vector must have 3 components.\n");
		return ;
	}
	vect_comp = ft_strsplit(str, ',');
	(*vector)[0] = ft_atof(&vect_comp[0][1]);
	(*vector)[1] = ft_atof(vect_comp[1]);
	(*vector)[2] = ft_atof(vect_comp[2]);
	ft_free_char_array(vect_comp);
}

static int	ft_valid_vector(char *line)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	if (line[i++] == '{')
	{
		while (count < 3 && ft_check_nbr(line, &i) == 1)
			count++;
	}
	if (count != 3 || line[i] != '}')
		return (0);
	return (1);
}

void		ft_fill_vector_fields(t_vector *vector, char *line)
{
	char	**fields;
	int		k;
	int		count;

	k = 1;
	count = 0;
	fields = ft_strsplit(line, ' ');
	while (fields[k] != NULL)
	{
		if (ft_valid_vector(fields[k]) == 1)
		{
			ft_add_vector_comp(fields[k], &(*vector));
			count++;
		}
		k++;
	}
	if (count == 0)
		ft_putstr("WARNING: vector must have default structure!\
Example: {1,2,3}.\n");
	ft_free_char_array(fields);
}
