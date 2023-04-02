/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:03:45 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/02 17:33:09 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_almost_all(t_args *arg, char *str)
{
	free_commands(arg->commands);
	free_tab(arg->path);
	free(arg);
	if (str)
		ft_print_error(str);
}

void	init_fill_tabs(t_args *arg)
{
	int	i;

	i = 0;
	arg->pid_tab = malloc(sizeof(pid_t) * arg->size);
	if (!arg->pid_tab)
		free_almost_all(arg, "pid_tab failed to malloc");
	arg->fd_tab = malloc(sizeof(int) * arg->size);
	if (!arg->fd_tab)
	{
		free(arg->pid_tab);
		free_almost_all(arg, "pid_tab failed to malloc");
	}
	while (i < arg->size - 1)
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
