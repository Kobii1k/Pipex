/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:29:52 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/22 12:24:37 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_big_path(char **envp)
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
		ft_print_error("couldnt found path");
	splitted = ft_split((envp[i] + 5), ':');
	if (!splitted)
		ft_print_error("malloc error");
	return (splitted);
}

char	*get_path(char **path, char **command)
{
	int		i;
	char	*str;

	i = 0;
	while (path[i])
	{
		str = ft_strjoin(path[i], "/");
		str = ft_strjoin_free(str, command[0]);
		if (access(str, F_OK) != -1)
			break ;
		i++;
		free(str);
	}
	if (!str)
		ft_print_error("no path exists where this command is executable");
	return (str);
}

char	***init_commands(int argc, char **argv)
{
	char	***commands;
	int		i;

	commands = malloc(sizeof(char **) * (argc - 2));
	if (!commands)
		ft_print_error("malloc error");
	i = 2;
	while (i < (argc - 1))
	{
		commands[i - 2] = ft_split(argv[i], ' ');
		if (!commands[i - 2])
			ft_print_error("split failed");
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
}
