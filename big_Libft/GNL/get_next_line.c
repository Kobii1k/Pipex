/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:45:25 by mgagne            #+#    #+#             */
/*   Updated: 2022/12/06 14:16:21 by mgagne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cleanup_buffer(char *buff)
{
	int	j;
	int	i;

	j = 0;
	while (buff[j] && buff[j] != '\n')
		j++;
	if (!buff[j])
		return ;
	j++;
	i = 0;
	while (buff[j])
		buff[i++] = buff[j++];
	buff[i] = '\0';
}

char	*ft_cleanup_line(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	j = 0;
	if (line[i] == '\0')
		tmp = malloc(sizeof(char) * (i + 1));
	else
		tmp = malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (NULL);
	while (j <= i)
	{
		tmp[j] = line[j];
		j++;
	}
	if (line[i] == '\0')
		j--;
	tmp[j] = '\0';
	free(line);
	return (tmp);
}

char	*ft_read_nl(int fd, char *buff, char *line)
{
	int		len;

	len = 1;
	while (len > 0 && ft_is_nl(buff) == -1)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			ft_bzero(buff, BUFFER_SIZE);
			return (free(line), NULL);
		}
		buff[len] = '\0';
		if (len == 0 && line[0] == '\0')
			return (free(line), NULL);
		line = ft_strjoin_free(line, buff);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*ft_read(int fd, char *buff)
{
	char	*line;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (buff)
	{
		line = ft_strjoin_free(line, buff);
		if (!line)
			return (NULL);
	}
	line = ft_read_nl(fd, buff, line);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	buff[BUFFER_SIZE] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read(fd, buff);
	if (!line)
		return (NULL);
	if (!line[0])
		return (free(line), NULL);
	line = ft_cleanup_line(line);
	if (!line)
		return (NULL);
	ft_cleanup_buffer(buff);
	return (line);
}
