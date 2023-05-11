/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:11:28 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/11 17:11:08 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_no_command(char *str)
{
	char *res;

	res = ft_strjoin(str, ": command not found\n");
	if (!res)
		ft_print_error("malloc error\n");
	write(STDERR_FILENO, res, ft_strlen(str) + 20);
	free(res);
	return ;
}

void	ft_print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	exit(1);
}
