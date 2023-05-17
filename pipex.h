/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:34:34 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/17 19:21:50 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "big_libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

# define ERROR2 "Failed to duplicate fd (dup2 error)\n"
# define ERROR3 "(empty command)"
# define ERROR4 "Failed to pipe fd\n"
# define ERROR5 "Failed to create fork\n"
# define ERROR6 ": command not found\n"
# define ERROR7 "Malloc cannot be created\n"

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
void	ft_no_cmd(char *str);

//pipex_init
void	init_fill_tabs(t_args *arg);
char	***init_commands(t_args *arg, int argc, char **argv);
t_args	*init_arg(int argc, char **argv, char **envp);
char	**get_big_path(t_args *arg, char **envp);

//pipex_exec.c
void	exec_command(t_args *arg, int fd[2], char **command, int end);
void	handle_command(t_args *arg, char **command, int end);
void	handle_pipe(t_args *arg);

//pipex_utils.c
char	*get_path(char **path, char **command);
void	wait_close(t_args *arg, int fd);
void	add_pid(t_args *arg, pid_t pid);
void	free_tab(char **str);

//ft_free.c
void	free_almost_all(t_args *arg, char *str);
void	free_all(t_args *args, char *str);
void	free_arg_print(t_args *arg, char *str);
void	free_commands(char ***commands);
void	free_path_arg(t_args *arg, char *str);


void	cloz(t_args *arg);

#endif
