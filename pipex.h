/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:34:34 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/24 14:11:38 by mgagne           ###   ########.fr       */
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
	int		size;
	char	**path;
	char	**envp;
	int		fd;
	int		in_fd;
	int		out_fd;
	char	***commands;
	pid_t	*pid_tab;
	int		*fd_tab;
}				t_args;

//errors.c
void	ft_print_error(char *str);

//pipex_init
void	init_fill_tabs(t_args *arg);
t_args	*init_arg(int argc, char **argv, char **envp);
void	free_almost_all(t_args *arg, char *str);

//pipex_exec.c
void	exec_command(t_args *arg, int fd[2], char **command, int end);
void	handle_command(t_args *arg, char **command, int end);
void	handle_pipe(t_args *arg);

//pipex_utils.c
char	**get_big_path(t_args *arg, char **envp);
char	*get_path(char **path, char **command);
char	***init_commands(t_args *arg, int argc, char **argv);
void	wait_close(t_args *arg);
void	add_pid(t_args *arg, pid_t pid);

//ft_free.c
void	free_tab(char **str);
void	free_all(t_args *args, char *str);
void	free_arg_print(t_args *arg, char *str);
void	free_commands(char ***commands);
void	free_path_arg(t_args *arg, char *str);

#endif
