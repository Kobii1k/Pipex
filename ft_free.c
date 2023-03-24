/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:28:41 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/21 16:30:10 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_args *arg)
{
	int		i;

	i = 0;
	while (arg->commands[i])
	{
		free_tab(arg->commands[i]);
		i++;
	}
	free(arg->commands);
	free_tab(arg->path);
	free(arg);
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
