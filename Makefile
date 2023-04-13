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

server: $(NAME_SERVER)

$(NAME_SERVER): $(OBJS_SR)
	cc $(FLAGS) -o $(NAME_SERVER) $(OBJS_SR)

$(OBJS): $(SRCS) ./src/libft.h
	cc $(FLAGS) -c $(SRCS_SR)

client: $(NAME_CLIENT)

$(NAME_CLIENT): $(OBJS_CL)
	cc $(FLAGS) -o $(NAME_CLIENT) $(OBJS_CL)

$(OBJS_CL): $(SRCS_CL) ./src/libft.h
	cc $(FLAGS) -c $(SRCS_CL)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS) 

fclean:	clean
	rm -rf $(NAME) 

re:	fclean all

.PHONY: all clean fclean re
