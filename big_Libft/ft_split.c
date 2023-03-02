/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:10:01 by mgagne            #+#    #+#             */
/*   Updated: 2022/11/17 18:58:05 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	**free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static unsigned int	ft_skip(char *str, char sep, int switcher)
{
	unsigned int	i;

	i = 0;
	if (!switcher)
	{
		while (str[i] && (*(str + i) == sep))
			i++;
	}
	else
	{
		while (str[i] && !(*(str + i) == sep))
			i++;
	}
	return (i);
}

static int	ft_len_tab(char *str, char sep)
{
	int	len;
	int	i;

	len = 0;
	i = ft_skip(str, sep, 0);
	while (str[i])
	{
		i += ft_skip(str + i, sep, 1);
		i += ft_skip(str + i, sep, 0);
		len++;
	}
	return (len);
}

static char	*ft_strndup(char *str, unsigned int n)
{
	char			*ret;
	unsigned int	i;

	ret = malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	i_tab;
	unsigned int	len;
	unsigned int	i;

	if (!s)
		return (NULL);
	len = ft_len_tab((char *)s, c);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	i = ft_skip((char *)s, c, 0);
	i_tab = 0;
	while (s[i])
	{
		tab[i_tab] = ft_strndup((char *)s + i, ft_skip((char *)s + i, c, 1));
		if (!tab[i_tab])
			return (free_all(tab));
		i_tab++;
		i += ft_skip((char *)s + i, c, 1);
		i += ft_skip((char *)s + i, c, 0);
	}
	tab[len] = NULL;
	return (tab);
}
