/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:33:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/13 14:41:11 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_pipe(t_args *arg)
{

}

char	*get_path(char **envp)
{
	char	**splitted;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	splitted = ft_split(envp[i], ':');
	i = 0;
	while (splitted[i])
	{
		if (access(splitted[i], F_OK))
			break;
		i++;
	}
	if (!splitted[i])
		ft_print_error("no path exists where this command is executable");
	return (splitted[i]);
}

void	init_arg(t_args *arg, char **argv, char **envp)
{
	arg = malloc(sizeof(t_args));
	if (!arg)
		ft_print_error("malloc error");
	arg->path = get_path(envp);
	arg->in = argv[1];
	arg->out = argv[4];
	arg->in_fd = open(arg->in, O_RDONLY);
	arg->out_fd = open(arg->out, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (arg->in_fd == -1)
		ft_print_error("file 1 can't be opened");
	if (arg->out_fd == -1)
		ft_print_error("file 1 can't be opened");
	return ;
}

//files : argv[1] && argv[4]
//commands : argv[2] && argv[3]
int	main(int argc , char **argv, char **envp)
{
	t_args	arg;

	if (argc != 5)
		ft_print_error("\"./pipex infile cmd1 cmd2 outfile\"");
	init_arg(&arg, argv, envp);
	handle_pipe(&arg);



	//


		// ft_printf("%s\n", );


	//




	return (0);
}
