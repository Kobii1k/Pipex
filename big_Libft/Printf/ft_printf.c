/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:02:55 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/24 10:01:50 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_conversion(char c, va_list args)
{
	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	if (c == 's')
		return (ft_print_str(va_arg(args, char *)));
	if (c == 'p')
		return (ft_print_hexa_pointer(va_arg(args, void *)));
	if (c == 'd')
		return (ft_print_int(va_arg(args, int)));
	if (c == 'i')
		return (ft_print_int(va_arg(args, int)));
	if (c == 'u')
		return (ft_print_uint(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_print_hexa(va_arg(args, int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_print_hexa(va_arg(args, int), "0123456789ABCDEF"));
	if (c == '%')
		return (ft_print_char('%'));
	return (0);
}

ssize_t	ft_convert_str(const char *format, va_list args)
{
	ssize_t	i;
	ssize_t	len;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			len += ft_print_conversion(format[i], args);
		}
		else if (format[i] != '%')
			len += ft_print_char(format[i]);
		i++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	ssize_t	len;
	va_list	args;

	len = write(1, 0, 0);
	if (len < 0)
		return (-1);
	va_start(args, format);
	len = ft_convert_str(format, args);
	va_end(args);
	return (len);
}
