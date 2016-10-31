/*
** client.h for in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sat May 21 03:22:28 2016 Sebastien Fourtou
** Last update Sun Jun  5 09:00:26 2016 Sebastien Fourtou
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_client t_client;

typedef struct s_fct
{
  char *commands[10];
  void (*fct_ptr[10])(t_client *);
} t_fct;

typedef struct s_client
{
  char *buffer_cin;
  char *buffer_server;
  int client_socket;
  char * nickname;
  int is_connected;
  t_fct fct;
} t_client;

//client-server
void send_server(int cs, t_client * client);
void read_server(int cs, t_client * client);
int connect_server(t_client *, int port);
void prepare_connect_server(t_client * client);

//output-input
void read_input(t_client * client);
void write_client(t_client * client);
void check_command(t_client * client, int);

//command
char * get_command(char * buffer);
int is_command(char * command, t_fct fct);
void exec_command(int idx, t_client * client);

//miscelleanous
void change_nickname(t_client * client);
void list_users(t_client * client);
void list_users_channel(t_client  * client);

//channels
void join_channel(t_client * client);
void list_channel(t_client * client);
void quit_channel(t_client * client);

//messages
void manage_messages(t_client * client);

//manage_fd
void init_my_sockets(fd_set *, fd_set *, int fd);
#endif
