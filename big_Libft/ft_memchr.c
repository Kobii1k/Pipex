/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:50:16 by mgagne            #+#    #+#             */
/*   Updated: 2023/01/28 02:08:49 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	if (!s)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (*(char *)(s + i) == (char)(c))
			return ((unsigned char *)(s + i));
		i = i + 1;
	}
	return (NULL);
}
