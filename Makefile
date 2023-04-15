//THIS MAKEFILE IS  NOT COMPLETE, IT WILL NOT WORK. IF YOU WISH TO COMPILE THIS PROGRAM, USE THE COMMAND LINES IMPLIED ON  SERVER/CLIENT SECTORS OF THIS CODE.

NAME_SERVER = minitalk_server
NAME_CLIENT = minitalk_client
FLAGS             = -Wall -Wextra -Werror -g3

FILES_BT =	bt_*.c \
			server.c

FILES_CLIENT = cl_*.c \
				bt_*.c \
				client.c

PATH_SRC	= ./src/
SRCS_CL		= $(addprefix $(PATH_SRC), $(FILES_CLIENT))
SRCS_SR		= $(addprefix $(PATH_SRC), $(FILES_BT))
OBJS_CL		= $(FILES_BT:.c=.o)
OBJS_SR		= $(FILES_CLIENT:.c=.o)

all:

server:
	gcc -o server ./src/server.c ./src/cl_*.c ./src/bt_*.c

client:
	gcc -o client ./src/client.c ./src/cl_*.c ./src/bt_*.c
	
server_bonus:
	gcc -o server_bonus ./src/server.c ./src/cl_*.c ./src/bt_*.c

client_bonus:
	gcc -o client_bonus ./src/client.c ./src/cl_*.c ./src/bt_*.c

clean:
	rm -rf $(OBJS_CL) $(OBJS_SR) 

fclean:	clean
	rm -rf $(NAME) 

re:	fclean all

.PHONY: all clean fclean re
