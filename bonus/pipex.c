/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:33:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/29 16:11:34 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	*arg;

	if (argc < 5)
		ft_print_error("\"./pipex infile [cmd1 cmd2 ...] outfile\"");
	arg = init_arg(argc, argv, envp);
	handle_pipe(arg);
	wait_close(arg);
	free_all(arg, NULL);
	return (0);
}
