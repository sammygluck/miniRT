/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:02:16 by wmarien           #+#    #+#             */
/*   Updated: 2024/02/28 15:57:45 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	process_decimal(float *nbr, const char *nptr, unsigned long *i)
{
	unsigned int	dec;

	dec = 10;
	(*i)++;
	while (nptr[*i] != '\0' && ft_isdigit(nptr[*i]))
	{
		*nbr += (float)(nptr[(*i)++] - '0') / dec;
		dec *= 10;
	}
}

float	ft_atof(const char *nptr)
{
	unsigned long	i;
	float			nbr;
	int				sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (nptr[i] != '\0' && (nptr[i] == 32
			|| nptr[i] == '\t' || nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f'))
		i++;
	if (nptr[i] != '\0' && nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && (ft_isdigit(nptr[i])))
		nbr = (nbr * 10) + (nptr[i++] - '0');
	if (nptr[i] == '.')
		process_decimal(&nbr, nptr, &i);
	return ((float)(nbr * sign));
}
