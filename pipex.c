/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:33:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/29 15:34:41 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	arg->in_fd = open(argv[1], O_RDONLY);
	if (arg->in_fd == -1)
		free_arg_print(arg, "file 1 can't be opened");
	arg->out_fd = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (arg->out_fd == -1)
		free_arg_print(arg, "file 2 can't be opened");
	arg->envp = envp;
	arg->path = get_big_path(arg, envp);
	arg->commands = init_commands(arg, argc, argv);
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
	free_all(arg, NULL);
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
