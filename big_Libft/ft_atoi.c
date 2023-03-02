/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:13:16 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/22 11:44:53 by mgagne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(int negative)
{
	if (negative == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				negative;
	long int		result;

	i = 0;
	negative = 1;
	result = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i])
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		if (result != (result * 10 + (str[i] - '0')) / 10)
			return (ft_overflow(negative));
		result *= 10;
		result += (int)str[i] - '0';
		i++;
	}
	return ((int) result * negative);
}
