/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:33:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/08 13:04:16 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_args	*init_arg(char **argv, char **envp)
{
	t_args	*arg;
	int		i;

	arg = malloc(sizeof(t_args));
	if (!arg)
		ft_print_error("malloc error");
	arg->argv = argv;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	arg->path = ft_split(envp[i], ':');
	return (arg);
}


//files : argv[1] && argv[4]
//commands : argv[2] && argv[3]
int	main(int argc , char **argv, char **envp)
{
	t_args	*arg;
	int		i;

	if (argc != 5)
		ft_print_error("\"./pipex file1 cmd1 cmd2 file2\"");
	arg = init_arg(argv, envp);
	i = 0;
	while (arg->path[i])
	{
		if (access())
	}



	//


		// ft_printf("%s\n", arg->path[i++]);


	//




	return (0);
}
