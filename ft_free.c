/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:28:41 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/02 17:32:14 by mgagne           ###   ########.fr       */
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

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_all(t_args *arg, char *str)
{
	free_commands(arg->commands);
	free_tab(arg->path);
	free(arg->pid_tab);
	free(arg->fd_tab);
	free(arg);
	if (str)
		ft_print_error(str);
}

void	free_arg_print(t_args *arg, char *str)
{
	free(arg);
	ft_print_error(str);
}

void	free_path_arg(t_args *arg, char *str)
{
	free_tab(arg->path);
	free(arg);
	ft_print_error(str);
}

