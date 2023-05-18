/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:28:41 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/18 17:01:56 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_commands(char ***commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		free_tab(commands[i]);
		i++;
	}
	free(commands);
}

void	close_files(t_args *arg)
{
	if (arg->in_fd != -1)
		close(arg->in_fd);
	if (arg->out_fd != -1)
		close(arg->out_fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	free_arg_print(t_args *arg, char *str)
{
	close_files(arg);
	free(arg);
	ft_print_error(str);
}

void	free_path_arg(t_args *arg, char *str)
{
	close_files(arg);
	free_tab(arg->path);
	free(arg);
	ft_print_error(str);
}

void	free_almost_all(t_args *arg, char *str)
{
	close_files(arg);
	free_commands(arg->commands);
	free_tab(arg->path);
	free(arg);
	ft_print_error(str);
}

void	free_all(t_args *arg, char *str)
{
	close_files(arg);
	free_commands(arg->commands);
	free_tab(arg->path);
	free(arg->pid_tab);
	free(arg->fd_tab);
	free(arg);
	if (str)
		ft_print_error(str);
}
