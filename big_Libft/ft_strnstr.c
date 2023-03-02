/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:49:14 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/17 18:48:39 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack,
	const char *needle, size_t len)
{
	size_t	i;
	size_t	u;
	size_t	temp;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		u = 0;
		temp = i;
		while (haystack[i] == needle[u] && i < len)
		{
			i++;
			u++;
			if (needle[u] == '\0')
				return ((char *)&haystack[i - u]);
		}
		i = temp + 1;
	}
	return (0);
}
