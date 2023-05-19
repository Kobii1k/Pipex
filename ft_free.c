/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:28:41 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/19 14:32:59 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_commands(char ***commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		free_tab_str(commands[i]);
		i++;
	}
	free(commands);
}

void	free_arg_print(t_args *arg, char *str)
{
	close_fds(arg, 1);
	free(arg);
	ft_error_exit(str);
}

void	free_path_arg(t_args *arg, char *str)
{
	close_fds(arg, 1);
	free_tab_str(arg->path);
	free(arg);
	ft_error_exit(str);
}

void	free_almost_all(t_args *arg, char *str)
{
	close_fds(arg, 1);
	free_commands(arg->commands);
	free_tab_str(arg->path);
	free(arg);
	ft_error_exit(str);
}

void	free_all(t_args *arg, char *str)
{
	close_fds(arg, 1);
	free_commands(arg->commands);
	free_tab_str(arg->path);
	free(arg->pid_tab);
	free(arg->fd_tab);
	free(arg);
	if (str)
		ft_error_exit(str);
}
