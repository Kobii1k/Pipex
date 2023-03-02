NAME	= libft.a

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strdup.c ft_strncmp.c ft_toupper.c ft_tolower.c ft_atoi.c ft_strnstr.c ft_memset.c ft_bzero.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_calloc.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_striteri.c ft_strmapi.c ft_strjoin.c ft_strtrim.c ft_substr.c ft_itoa.c GNL/get_next_line.c GNL/get_next_line_utils.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS	= ${SRCS:.c=.o}

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

PRINTF	= ./Printf/

%.o:		%.c Makefile libft.h
	${CC} ${CFLAGS} -I . -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} printf
			ar rc ${NAME} ${OBJS}

all:		 ${NAME}

clean:
			rm -f ${OBJS}
			${MAKE} clean -C ${PRINTF}

fclean:		clean
			rm -f ${NAME}
			${MAKE} fclean -C ${PRINTF}

re:			fclean all

printf:		${PRINTF}
			${MAKE} all -C ${PRINTF}

.PHONY:		all clean fclean re printf
