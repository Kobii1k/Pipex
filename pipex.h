/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:34:34 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/13 14:20:58 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "big_Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_args
{
	char	*path;

	char	*in;
	char	*out;
	int		in_fd;
	int		out_fd;
}				t_args;

//errors.c
void	ft_print_error(char *str);


//pipex.c

#endif
