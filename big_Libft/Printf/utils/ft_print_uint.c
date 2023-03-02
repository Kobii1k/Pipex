/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:42:44 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/23 21:54:55 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

ssize_t	ft_print_uint(unsigned int nb)
{
	ssize_t	len;

	len = 0;
	if (nb >= 10)
	{
		len += ft_print_uint(nb / 10);
		len += ft_print_uint(nb % 10);
	}
	else
		len += ft_print_char(nb + '0');
	return (len);
}
