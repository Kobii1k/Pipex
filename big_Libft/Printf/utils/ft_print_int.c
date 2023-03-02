/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:42:39 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/23 19:12:46 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

ssize_t	ft_print_int(int n)
{
	long	nb;
	ssize_t	len;

	len = 0;
	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		len += write(1, "-", 1);
	}
	if (nb >= 10)
	{
		len += ft_print_int((int)(nb / 10));
		len += ft_print_int((int)(nb % 10));
	}
	else
		len += ft_print_char(nb + '0');
	return (len);
}
