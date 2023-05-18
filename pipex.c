/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:33:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/18 17:44:54 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	*arg;

	if (argc != 5)
		ft_error_exit("Wrong number of arguments\n");
	arg = init_arg(argc, argv, envp);
	handle_pipes(arg);
	wait_close(arg, -1);
	free_all(arg, NULL);
	return (0);
}
