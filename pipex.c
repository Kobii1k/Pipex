/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:33:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/24 00:54:49 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_close(t_args *arg)
{
	int	i;

	i = 0;
	while (i < arg->size)
	{
		waitpid(arg->pid_tab[i], NULL, 0);
		close(arg->fd_tab[i]);
		i++;
	}
}

void	add_pid(t_args *arg, pid_t pid)
{
	int	i;

	i = 0;
	while (i < arg->size)
	{
		if (arg->pid_tab[i] < 0)
			break ;
		i++;
	}
	arg->pid_tab[i] = pid;
	arg->fd_tab[i] = arg->fd;
}

void	exec_command(t_args *arg, int fd[2], char **command, int end)
{
	char	*path;

	close(fd[0]);
	if (dup2(arg->fd, STDIN_FILENO) == -1)
		ft_print_error("dup2 failed");
	if (end == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_print_error("dup2 failed");
	}
	path = get_path(arg->path, command);
	if (execve(path, command, arg->envp) == -1)
		ft_print_error("execution failed");
}

void	handle_command(t_args *arg, char **command, int end)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_print_error("pipe function failed");
	pid = fork();
	if (pid == -1)
		ft_print_error("fork function failed");
	else if (pid == 0)
		exec_command(arg, fd, command, end);
	add_pid(arg, pid);
	close(fd[1]);
	arg->fd = fd[0];
}

//fd[0] => read end of the pipe
//fd[1] => write end of the pipe
void	handle_pipe(t_args *arg)
{
	int	i;

	if (dup2(arg->in_fd, STDIN_FILENO) == -1)
		ft_print_error("dup2 error");
	if (dup2(arg->out_fd, STDOUT_FILENO) == -1)
		ft_print_error("dup2 error");
	arg->fd = STDIN_FILENO;
	i = 0;
	while (arg->commands[i + 1])
	{
		handle_command(arg, arg->commands[i], 0);
		i++;
	}
	handle_command(arg, arg->commands[i], 1);
}

void	init_fill_tabs(t_args *arg)
{
	int	i;

	i = 0;
	arg->pid_tab = malloc(sizeof(pid_t) * arg->size);
	if (!arg->pid_tab)
		ft_print_error("pid_tab failed to malloc");
	arg->fd_tab = malloc(sizeof(int) * arg->size);
	if (!arg->fd_tab)
		ft_print_error("pid_tab failed to malloc");
	while (i < arg->size)
	{
		arg->pid_tab[i] = -1;
		i++;
	}
}

t_args	*init_arg(int argc, char **argv, char **envp)
{
	t_args	*arg;

	arg = malloc(sizeof(t_args));
	if (!arg)
		ft_print_error("malloc error");
	arg->size = argc - 3;
	arg->path = get_big_path(envp);
	arg->envp = envp;
	arg->in_fd = open(argv[1], O_RDONLY);
	arg->out_fd = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (arg->in_fd == -1)
		ft_print_error("file 1 can't be opened");
	if (arg->out_fd == -1)
		ft_print_error("file 2 can't be opened");
	arg->commands = init_commands(argc, argv);
	init_fill_tabs(arg);
	return (arg);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*arg;

	if (argc < 5)
		ft_print_error("\"./pipex infile [cmd1 cmd2 ...] outfile\"");
	arg = init_arg(argc, argv, envp);
	handle_pipe(arg);
	wait_close(arg);
	free_all(arg);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_args	*arg;

// 	if (argc != 5)
// 		ft_print_error("\"./pipex infile cmd1 cmd2 outfile\"");
// 	arg = init_arg(argv, envp);
// 	handle_pipe(arg, envp);
// 	free_tab(arg->command_one);
// 	free_tab(arg->command_two);
// 	free_tab(arg->path);
// 	free(arg);
// 	return (0);
// }
