/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:00:12 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/19 14:23:45 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	*arg;

	if (argc < 5)
		ft_print_str("\"./pipex infile [cmd1 cmd2 ...] outfile\"\n");
	arg = init_arg(argc, argv, envp);
	handle_pipes(arg);
	wait_close(arg, -1);
	free_all(arg, NULL);
	return (0);
}
