/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:11:28 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/18 17:42:01 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_no_cmd(char *str)
{
	char	*res;

	res = ft_strjoin(str, ERROR6);
	if (!res)
		ft_error_exit("malloc error\n");
	write(STDERR_FILENO, res, ft_strlen(str) + 20);
	free(res);
	return ;
}

void	ft_error_exit(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i != 0)
		write(STDERR_FILENO, str, i);
	exit(1);
}
