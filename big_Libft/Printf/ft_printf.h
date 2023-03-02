/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:11:54 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/24 09:45:05 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

int		ft_printf(const char *format, ...);

ssize_t	ft_print_char(int c);
ssize_t	ft_print_str(char *s);
ssize_t	ft_print_int(int n);
ssize_t	ft_print_uint(unsigned int nb);
ssize_t	ft_print_hexa(int n, char *base);
ssize_t	ft_print_hexa_pointer(void *p);

char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

#endif
