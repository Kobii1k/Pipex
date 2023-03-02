NAME	= ../libftprintf.a

SRCS	=	ft_printf.c utils/ft_print_char.c utils/ft_print_hexa.c utils/ft_print_int.c utils/ft_print_str.c utils/ft_print_uint.c utils/ft_print_hexa_pointer.c utils/ft_strlen.c

OBJS	= ${SRCS:.c=.o}

CC				= cc

CFLAGS 			= -Wall -Werror -Wextra

%.o:			%.c Makefile ft_printf.h
						${CC} ${CFLAGS} -I . -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
				ar rcs ${NAME} ${OBJS}

all:			${NAME}

clean:
						rm -f ${OBJS}

fclean:			clean
						rm -f ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
