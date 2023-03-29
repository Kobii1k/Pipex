NAME			= pipex

NAME_BONUS		= pipex_bonus

SRCS			= pipex.c errors.c ft_free.c pipex_utils.c pipex_exec.c pipex_init.c

SRCS_BONUS		= ./bonus/pipex.c errors.c ft_free.c pipex_utils.c pipex_exec.c pipex_init.c

OBJS			= ${SRCS:.c=.o}

OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

CC				= cc

CFLAGS 			= -Wall -Werror -Wextra -g3 -fsanitize=address

BIGLIBFT		= ./big_Libft/

%.o:			%.c Makefile pipex.h
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
				${MAKE} all -C ${BIGLIBFT}
				${CC} ${CFLAGS} ${OBJS} big_Libft/libft.a big_Libft/printfd.a big_Libft/printf.a -o ${NAME}

${NAME_BONUS}:	${OBJS_BONUS}
				${MAKE} all -C ${BIGLIBFT}
				${CC} ${CFLAGS} ${OBJS_BONUS} big_Libft/libft.a big_Libft/printfd.a big_Libft/printf.a -o ${NAME_BONUS}

all:			${NAME}

bonus:			${NAME_BONUS}

clean:
				rm -f ./bonus/pipex.o ${OBJS}
				${MAKE} clean -C ${BIGLIBFT}

fclean:			clean
				rm -f ${NAME} ${NAME}_bonus
				${MAKE} fclean -C ${BIGLIBFT}

re:				fclean all

.PHONY:			all clean fclean re bonus
