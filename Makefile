NAME			= pipex

SRCS			= pipex.c errors.c

OBJS			= ${SRCS:.c=.o}

CC				= cc

CFLAGS 			= -Wall -Werror -Wextra

BIGLIBFT		= ./big_Libft/

%.o:			%.c Makefile push_swap.h
				${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} biglibft
				${CC} ${OBJS} -g big_Libft/libft.a big_Libft/printfd.a big_Libft/printf.a -o ${NAME}

all:			${NAME}

clean:
				rm -f ${OBJS}
				${MAKE} clean -C ${BIGLIBFT}

fclean:			clean
				rm -f ${NAME}
				${MAKE} fclean -C ${BIGLIBFT}

re:				fclean all

biglibft:		${BIGLIBFT}
				${MAKE} all -C ${BIGLIBFT}

.PHONY:			all clean fclean re biglibft
