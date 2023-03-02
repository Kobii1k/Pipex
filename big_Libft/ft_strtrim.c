/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:33:24 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/16 16:00:33 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_set(char c, const char *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*empty_string(void)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;

	if (!(s1 && set))
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (end == 0)
		return (empty_string());
	end--;
	while (start <= end && is_set(s1[start], set))
		start++;
	while (end >= start && is_set(s1[end], set))
		end--;
	i = 0;
	str = malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
