/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:03:45 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/01 12:34:36 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	contains_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	init_fill_tabs(t_args *arg)
{
	int	i;

	arg->pid_tab = malloc(sizeof(pid_t) * arg->size);
	if (!arg->pid_tab)
		free_almost_all(arg, ERROR7);
	arg->fd_tab = malloc(sizeof(int) * arg->size);
	if (!arg->fd_tab)
	{
		free(arg->pid_tab);
		free_almost_all(arg, ERROR7);
	}
	i = 0;
	while (i < arg->size)
	{
		arg->pid_tab[i] = -1;
		arg->fd_tab[i] = 1;
		i++;
	}
}

static char	***init_commands(t_args *arg, int argc, char **argv)
{
	char	***commands;
	int		i;

	commands = malloc(sizeof(char **) * (argc - 2));
	if (!commands)
		free_path_arg(arg, ERROR7);
	i = 2;
	while (i < (argc - 1))
	{
		commands[i - 2] = ft_split(argv[i], ' ');
		if (!commands[i - 2])
		{
			arg->commands = commands;
			free_almost_all(arg, ERROR7);
		}
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
}

char	**get_big_path(t_args *arg, char **envp)
{
	char	**splitted;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		free_arg_print(arg, "$PATH variable parse error\n");
	splitted = ft_split((envp[i] + 5), ':');
	if (!splitted)
		free_arg_print(arg, ERROR7);
	return (splitted);
}

t_args	*init_arg(int argc, char **argv, char **envp)
{
	t_args	*arg;

	arg = malloc(sizeof(t_args));
	if (!arg)
		ft_error_exit(ERROR7);
	arg->size = argc - 3;
	arg->in_fd = open(argv[1], O_RDONLY);
	if (arg->in_fd == -1)
		perror(argv[1]);
	arg->out_fd = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (arg->out_fd == -1)
		perror(argv[argc - 1]);
	arg->envp = envp;
	arg->path = get_big_path(arg, envp);
	arg->commands = init_commands(arg, argc, argv);
	init_fill_tabs(arg);
	return (arg);
}
