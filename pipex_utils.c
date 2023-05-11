/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:29:52 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/11 17:17:39 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		free_arg_print(arg, "$PATH variable does not exist\n");
	splitted = ft_split((envp[i] + 5), ':');
	if (!splitted)
		free_arg_print(arg, "Malloc cannot be created\n");
	return (splitted);
}

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

char	***init_commands(t_args *arg, int argc, char **argv)
{
	char	***commands;
	int		i;

	commands = malloc(sizeof(char **) * (argc - 2));
	if (!commands)
		free_path_arg(arg, "malloc error\n");
	i = 2;
	while (i < (argc - 1))
	{
		commands[i - 2] = ft_split(argv[i], ' ');
		if (!commands[i - 2])
		{
			arg->commands = commands;
			free_almost_all(arg, "malloc error\n");
		}
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
}

void	wait_close(t_args *arg)
{
	int	i;

	i = arg->size - 1;
	while (i > 0)
	{
		if (arg->pid_tab[i] != -1)
		{
			waitpid(arg->pid_tab[i], NULL, 0);
			close(arg->fd_tab[i]);
		}
		i--;
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
