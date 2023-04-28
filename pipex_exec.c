/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:05:59 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/28 15:25:13 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_command(t_args *arg, int fd[2], char **command, int end)
{
	char	*path;

	close(fd[0]);
	if (dup2(arg->fd, STDIN_FILENO) == -1)
		free_all(arg, "dup2 failed\n");
	if (end == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			free_all(arg, "dup2 failed\n");
	}
	path = get_path(arg->path, command);
	if (!path || execve(path, command, arg->envp) == -1)
		free_all(arg, "Command not found\n");
}

void	handle_command(t_args *arg, char **command, int end)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		wait_close(arg);
		free_all(arg, "pipe function failed\n");
	}
	pid = fork();
	if (pid == -1)
	{
		wait_close(arg);
		free_all(arg, "fork function failed\n");
	}
	else if (pid == 0)
		exec_command(arg, fd, command, end);
	add_pid(arg, pid);
	close(fd[1]);
	arg->fd = fd[0];
}

void	handle_pipe(t_args *arg)
{
	int	i;

	if (arg->in_fd != -1 && dup2(arg->in_fd, STDIN_FILENO) == -1)
		free_all(arg, "dup2 error\n");
	if (dup2(arg->out_fd, STDOUT_FILENO) == -1)
		free_all(arg, "dup2 error\n");
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
	handle_command(arg, arg->commands[i], 1);
}
