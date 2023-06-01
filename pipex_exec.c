/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:05:59 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/01 12:34:22 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execute(t_args *arg, char **command)
{
	char	*path;

	if (access(command[0], F_OK) == -1)
	{
		if (command[0][0] == '.' || command[0][0] == '/')
			return (perror(command[0]), 1);
		path = get_path(arg->path, command);
		if (!path)
			return (free(path), ft_no_cmd(command[0]), 1);
		if (execve(path, command, arg->envp) == -1)
			return (free(path), ft_no_cmd(command[0]), 1);
		if (path)
			free(path);
	}
	else
	{
		if (contains_slash(command[0]))
		{
			if (execve(command[0], command, arg->envp) == -1)
				return (perror(command[0]), 1);
		}
		else
			return (ft_no_cmd(command[0]), 1);
	}
	return (0);
}

static void	exec_command(t_args *arg, int fd[2], char **command, int end)
{
	close(fd[0]);
	if (dup2(arg->fd, STDIN_FILENO) == -1)
	{
		close(arg->fd);
		return (wait_close(arg, fd[1]), free_all(arg, ERROR2));
	}
	if (arg->fd != 1)
	{
		close(arg->in_fd);
		if (end != -1)
			close(arg->fd);
	}
	if (end != 1 && dup2(fd[1], STDOUT_FILENO) == -1)
		return (wait_close(arg, fd[1]), free_all(arg, ERROR2));
	close(fd[1]);
	close_fds(arg, 0);
	if (!command[0])
		return (ft_no_cmd(ERROR3), wait_close(arg, -1), free_all(arg, ""));
	else if (execute(arg, command))
		return (wait_close(arg, -1), free_all(arg, ""));
	return (wait_close(arg, -1), free_all(arg, NULL), exit(0));
}

static void	handle_command(t_args *arg, char **command, int end)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (wait_close(arg, -1), free_all(arg, ERROR4));
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(arg->fd);
		return (wait_close(arg, -1), free_all(arg, ERROR5));
	}
	else if (pid == 0)
		exec_command(arg, fd, command, end);
	add_pid(arg, pid);
	close(fd[1]);
	if (end == 1 || arg->out_fd == -1)
		close(fd[0]);
	arg->fd = fd[0];
}

static void	dup_fds(t_args *arg)
{
	if (arg->out_fd != -1)
	{
		if (dup2(arg->out_fd, STDOUT_FILENO) == -1)
		{
			close(arg->in_fd);
			close(arg->out_fd);
			free_all(arg, ERROR2);
		}
		close(arg->out_fd);
	}
}

void	handle_pipes(t_args *arg)
{
	int	i;

	dup_fds(arg);
	i = 0;
	if (arg->in_fd == -1)
		arg->fd = 1;
	else
		arg->fd = arg->in_fd;
	while (arg->commands[i + 1])
	{
		if (i == 0)
		{
			if (arg->in_fd != -1)
				handle_command(arg, arg->commands[i], -1);
		}
		else
			handle_command(arg, arg->commands[i], 0);
		i++;
	}
	if (arg->out_fd != -1)
		handle_command(arg, arg->commands[i], 1);
}
