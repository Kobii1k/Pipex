/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:05:59 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/12 17:02:53 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	exec_command(t_args *arg, int fd[2], char **command, int end)
{
	char	*path;

	close(fd[0]);
	if (dup2(arg->fd, STDIN_FILENO) == -1)
		free_all(arg, "Failed to duplicate fd (dup2 error)\n");
	if (end == 0 && dup2(fd[1], STDOUT_FILENO) == -1)
		free_all(arg, "Failed to duplicate fd (dup2 error)\n");
	if (!command[0])
		return (ft_no_command("(empty command)"), free_all(arg, ""));
	else
	{
		if (access(command[0], F_OK) == -1)
		{
			if (command[0][0] == '.')
				return (perror(command[0]), free_all(arg, ""));
			path = get_path(arg->path, command);
			if (!path || execve(path, command, arg->envp) == -1)
				return (ft_no_command(command[0]), free_all(arg, ""));
			if (path)
				free(path);
		}
		else if (execve(command[0], command, arg->envp) == -1)
			return (free_all(arg, ""));
	}
	return (free_all(arg, NULL), exit(0));
}

void	handle_command(t_args *arg, char **command, int end)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		wait_close(arg);
		free_all(arg, "Failed to pipe fd\n");
	}
	pid = fork();
	if (pid == -1)
	{
		wait_close(arg);
		free_all(arg, "Failed to create fork\n");
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
		free_all(arg, "Failed to duplicate fd (dup2 error)\n");
	if (arg->out_fd != -1 && dup2(arg->out_fd, STDOUT_FILENO) == -1)
		free_all(arg, "Failed to duplicate fd (dup2 error)\n");
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
