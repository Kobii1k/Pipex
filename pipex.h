/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:34:34 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/20 18:50:12 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "big_Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	char	**path;
	char	**envp;

	int		fd;

	int		in_fd;
	int		out_fd;

	char	***commands;
}				t_args;

//errors.c
void	ft_print_error(char *str);

//pipex.c

//pipex_utils.c
char	**get_big_path(char **envp);
char	*get_path(char **path, char **command);
char	***init_commands(int argc, char **argv);

//ft_free.c
void	free_tab(char **str);
#endif
