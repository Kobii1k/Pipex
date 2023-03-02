/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:03:51 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/10 17:07:26 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*pointer;

	pointer = s;
	while (n)
	{
		*pointer = (unsigned char)c;
		pointer++;
		n--;
	}
	return (s);
}
