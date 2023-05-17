/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:05:59 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/17 16:24:11 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(t_args *arg, char **command)
{
	char	*path;

	if (access(command[0], F_OK) == -1)
	{
		if (command[0][0] == '.' || command[0][0] == '/')
			return (perror(command[0]), 1);
		path = get_path(arg->path, command);
		if (path)
			if (execve(path, command, arg->envp) == -1)
				return (free(path), ft_no_cmd(command[0]), 1);
		if (path)
			free(path);
	}
	else if (execve(command[0], command, arg->envp) == -1)
		return (perror(command[0]), 1);
	return (0);
}

void	exec_command(t_args *arg, int fd[2], char **command, int end)
{
	close(fd[0]);
	if (arg->fd != -1)
	{
		if (dup2(arg->fd, STDIN_FILENO) == -1)
		{
			close(arg->fd);
			return (wait_close(arg, fd[1]), free_all(arg, ERROR2));
		}
		close(arg->fd);
	}
	if (end == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (wait_close(arg, fd[1]), free_all(arg, ERROR2));
	}
	close(fd[1]);
	if (!command[0])
		return (ft_no_cmd(ERROR3), wait_close(arg, -1), free_all(arg, ""));
	else
		if (execute(arg, command) == 1)
			return (wait_close(arg, -1), free_all(arg, ""));
	return (wait_close(arg, -1), free_all(arg, NULL), exit(0));
}

void	handle_command(t_args *arg, char **command, int end)
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
		close(arg->in_fd);
		return (wait_close(arg, -1), free_all(arg, ERROR5));
	}
	else if (pid == 0)
		exec_command(arg, fd, command, end);
	add_pid(arg, pid);
	close(fd[1]);
	if (end == 1)
		close(fd[0]);
	else
		arg->fd = fd[0];
}

void	dup_fds(t_args *arg)
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
	// if (arg->in_fd != -1)
	// {
	// 	if (dup2(arg->in_fd, STDIN_FILENO) == -1)
	// 	{
	// 		close(arg->in_fd);
	// 		free_all(arg, ERROR2);
	// 	}
	// 	else
	// 		close(arg->in_fd);
	// }
}

void	handle_pipe(t_args *arg)
{
	int	i;

	dup_fds(arg);
	i = 2;
	arg->fd = arg->in_fd;
	i = 0;
	while (arg->commands[i + 1])
	{
		if (i == 0)
		{
			if (arg->in_fd != -1)
				handle_command(arg, arg->commands[i], 0);
		}
		else
			handle_command(arg, arg->commands[i], 0);
		i++;
	}
	if (arg->out_fd != -1)
		handle_command(arg, arg->commands[i], 1);
}
