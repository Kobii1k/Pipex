/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:05:59 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/12 19:56:26 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_args *arg, int fd[2], char **command)
{
	char	*path;

	if (access(command[0], F_OK) == -1)
	{
		if (command[0][0] == '.')
			return (wait_close(arg, fd[1]),
				perror(command[0]),
				free_all(arg, ""));
		path = get_path(arg->path, command);
		if (!path || execve(path, command, arg->envp) == -1)
			return (wait_close(arg, fd[1]),
				ft_no_cmd(command[0]),
				free_all(arg, ""));
		if (path)
			free(path);
	}
	else if (execve(command[0], command, arg->envp) == -1)
		return (wait_close(arg, fd[1]), free_all(arg, ""));
}

void	exec_command(t_args *arg, int fd[2], char **command, int end)
{
	close(fd[0]);
	if (dup2(arg->fd, STDIN_FILENO) == -1)
		return (wait_close(arg, fd[1]), free_all(arg, ERROR2));
	if (end == 0 && dup2(fd[1], STDOUT_FILENO) == -1)
		return (wait_close(arg, fd[1]), free_all(arg, ERROR2));
	if (!command[0])
		return (wait_close(arg, fd[1]), ft_no_cmd(ERROR3), free_all(arg, ""));
	else
		execute(arg, fd, command);
	return (wait_close(arg, fd[1]), free_all(arg, NULL), exit(0));
}

void	handle_command(t_args *arg, char **command, int end)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		wait_close(arg, -1);
		free_all(arg, ERROR4);
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		wait_close(arg, fd[1]);
		free_all(arg, ERROR5);
	}
	else if (pid == 0)
		exec_command(arg, fd, command, end);
	add_pid(arg, pid);
	close(fd[1]);
	if (end)
		close(fd[0]);
	else
		arg->fd = fd[0];
}

void	handle_pipe(t_args *arg)
{
	int	i;

	if (arg->in_fd != -1 && dup2(arg->in_fd, STDIN_FILENO) == -1)
		free_all(arg, ERROR2);
	if (arg->out_fd != -1 && dup2(arg->out_fd, STDOUT_FILENO) == -1)
		free_all(arg, ERROR2);
	arg->fd = STDIN_FILENO;
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
	{
		handle_command(arg, arg->commands[i], 1);
	}
}
