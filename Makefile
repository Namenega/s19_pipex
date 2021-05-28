SRCNAME 	=	srcs/main.c			\
				srcs/dquote.c

SRCS 		= ${SRCNAME}

OBJS 		= ${SRCS:.c=.o}

NAME		= pipex

CC 			= gcc
RM 			= rm -f
CFLAGS 		= -Wall -Wextra -Werror -I -I./include/libft

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		make -C ./include/libft
		${CC} -o ${NAME} ${OBJS} -L./include/libft -lft

all:		${NAME}

clean:
		make -C ./include/libft clean
		${RM} ${OBJS} ${NAME} ./include/libft/libft.a

fclean:		clean
		${RM} ${NAME} ./include/libft/libft.all

re: 		fclean all

c: 			all clean

.PHONY: 	clean fclean all re
