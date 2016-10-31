##
## Makefile for  in /Users/fourto_s/Projects/Epitech/Tek2/IRC
##
## Made by Sebastien Fourtou
## Login   <fourto_s@epitech.net>
##
## Started on  Fri May 20 22:55:46 2016 Sebastien Fourtou
## Last update Sun Jun  5 09:02:49 2016 Sebastien Fourtou
##

NAME_SERVER = ./server

NAME_CLIENT = ./client

SRC_SERVER = ./server_src/main.c \
	./server_src/manage_client.c \
	./server_src/manage_fds.c \
	./server_src/command.c \
	./server_src/miscelleanous.c \
	./server_src/my_channels.c \
	./server_src/channels_glob.c \
	./server_src/utils.c \
	./server_src/get_next_line.c \
	./server_src/my_str_to_wordtab.c \
	./server_src/message.c \
	./server_src/tmp.c \
	./server_src/verif.c

SRC_CLIENT = ./client_src/main.c \
	./client_src/client-server.c \
	./client_src/command.c \
	./client_src/output-input.c \
	./client_src/miscelleanous.c \
	./client_src/channels.c \
	./client_src/messages.c \
	./client_src/manage_sockets.c

DEST_SERVER = $(SRC_SERVER:.c=.o)

DEST_CLIENT = $(SRC_CLIENT:.c=.o)

CFLAGS = -g3

GCC = gcc


all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(DEST_SERVER)
	$(GCC) -o $(NAME_SERVER) $(DEST_SERVER)

$(NAME_CLIENT): $(DEST_CLIENT)
	$(GCC) -o $(NAME_CLIENT) $(DEST_CLIENT)

clean:
	$(RM) $(DEST_SERVER)
	$(RM) $(DEST_CLIENT)

fclean: clean
	$(RM) $(NAME_SERVER)
	$(RM) $(NAME_CLIENT)

re: fclean all
