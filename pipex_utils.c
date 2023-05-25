/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:29:52 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/25 15:53:48 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **path, char **command)
{
	int		i;
	char	*str;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			str = ft_strjoin(path[i], "/");
			if (!str)
				return (NULL);
			str = ft_strjoin_free(str, command[0]);
			if (!str)
				return (NULL);
			if (access(str, F_OK) != -1)
				return (str);
			i++;
			free(str);
		}
	}
	return (NULL);
}

void	close_fds(t_args *arg, int s)
{
	int	i;

	if (!s)
	{
		i = arg->size;
		while (--i >= 0)
		{
			if (arg->fd_tab[i] != 1)
				close(arg->fd_tab[i]);
		}
	}
	else
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	if (arg->in_fd != -1)
		close(arg->in_fd);
	if (arg->out_fd != -1)
		close(arg->out_fd);
}

void	wait_close(t_args *arg, int fd)
{
	int	i;

	if (fd != -1)
		close(fd);
	i = arg->size;
	while (--i >= 0)
	{
		waitpid(arg->pid_tab[i], NULL, 0);
		if (arg->fd_tab[i] != 1)
			close(arg->fd_tab[i]);
	}
}

void	add_pid(t_args *arg, pid_t pid)
{
	int	i;

	i = 0;
	while (arg->pid_tab[i] != -1 && i < arg->size)
		i++;
	if (i < arg->size)
	{
		arg->pid_tab[i] = pid;
		if (arg->fd != -1)
			arg->fd_tab[i] = arg->fd;
	}
}

void	free_tab_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
