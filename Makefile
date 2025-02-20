SRCS		=	pipex.c \
				ft_split.c \
				find_path.c \
				ft_strnstr.c \
				ft_strjoin.c \
				error.c \
				ft_strncmp.c \

OBJS		= ${SRCS:.c=.o}

NAME		= pipex

CC			= cc

RM 			= rm -f

CFLAGS		= -Wall -Wextra -Werror

HEADERS		= pipex.h

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS} ${HEADERS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
