/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa_pointer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:42:36 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/24 13:04:15 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static ssize_t	ft_loop_hexa(void *p)
{
	ssize_t		len;
	uintptr_t	nb;
	char		*base;

	base = "0123456789abcdef";
	nb = (uintptr_t)p;
	len = 0;
	if (nb >= 16)
	{
		len += ft_loop_hexa((void *)(nb / 16));
		len += ft_loop_hexa((void *)(nb % 16));
	}
	else
		len += ft_print_char(base[nb]);
	return (len);
}

ssize_t	ft_print_hexa_pointer(void *p)
{
	ssize_t		len;

	len = write(1, "0x", 2);
	len += ft_loop_hexa(p);
	return (len);
}
