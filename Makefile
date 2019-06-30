##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile for 42sh
##

CC	=	gcc

CFLAGS	=	-g3 -I./include -W -Wall -Wextra

SRC	=	src/main.c				\
		src/int_to_char.c			\
		src/word_array.c			\
		src/my_strcat.c			\
		src/tools.c			\
		src/error_handling.c			\
		src/ptr_fct.c			\
		src/client_side.c			\
		src/init_client.c			\
		src/data_sock.c			\
		src/server.c			\
		src/cmd/user.c			\
		src/cmd/cwd.c			\
		src/cmd/pass.c			\
		src/cmd/cdup.c			\
		src/cmd/quit.c			\
		src/cmd/dele.c			\
		src/cmd/pwd.c			\
		src/cmd/pasv.c			\
		src/cmd/port.c			\
		src/cmd/noop.c			\
		src/cmd/help.c			\
		src/cmd/retr.c			\
		src/cmd/stor.c			\
		src/cmd/list.c			\

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
