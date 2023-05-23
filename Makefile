NAME			= pipex

NAME_BONUS		= pipex_bonus

SRCS			= pipex.c errors.c ft_free.c pipex_utils.c pipex_exec.c pipex_init.c

SRCS_BONUS		= bonus/pipex_bonus.c errors.c ft_free.c pipex_utils.c pipex_exec.c pipex_init.c

OBJS			= ${SRCS:.c=.o}

OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

CC				= cc

CFLAGS 			= -Wall -Werror -Wextra

LIBFT			= ./big_libft/libft.a

LIBFTDIR		= ./big_libft

all:			lib ${NAME}

bonus:			lib ${NAME_BONUS}

%.o:			%.c Makefile pipex.h
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${LIBFT}
				${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${NAME_BONUS}:	${OBJS_BONUS} ${LIBFT}
				${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}

clean:
				rm -f ${OBJS}
				rm -f bonus/pipex_bonus.o
				${MAKE} clean -C ${LIBFTDIR}

fclean:			clean
				rm -f ${NAME} ${NAME_BONUS}
				${MAKE} fclean -C ${LIBFTDIR}

re:				fclean all

lib:
				${MAKE} -C ${LIBFTDIR}

.PHONY:			all bonus clean fclean re lib
