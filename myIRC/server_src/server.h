/*
** server.h for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sat May 21 02:13:44 2016 Sebastien Fourtou
** Last update Sun Jun  5 09:02:29 2016 Sebastien Fourtou
*/

#ifndef SERVER_H_
# define SERVER_H_

# define MAX_FD 255
# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*fct)();
typedef struct s_env t_env;

typedef struct s_fct
{
  char * commands[20];
  void (*fct_ptr[20])(t_env **);
} t_fct;

typedef struct s_channel
{
  char * name;
  int id_channel;
  struct s_channel * next;
} t_channel;

typedef struct s_env
{
  int fd;
  char fd_type;
  fct fct_read;
  fct fct_write;
  int port;
  char * nickname;
  char * last_message;
  char * reply;
  struct s_env * first;
  struct s_env * next;
  t_channel * channels;
  t_fct fct;
} t_env;

t_channel * ch;

//manage_client
void read_client(t_env ** env);
void write_client(t_env ** env);
void add_client(t_env ** env);

//manage_fds
void init_set_fd(t_env * env, fd_set * set_read, fd_set * set_write);
int get_max_fd(t_env * env);
void check_changes_fd(t_env ** env, fd_set * set_read, fd_set * set_write);

//command
int do_command(t_env ** env);
t_fct init_command();
void quit_all(t_env **env);

//miscelleanous
void change_nickname(t_env ** env);
void list_users(t_env ** env);
void list_users_channel(t_env ** env);
void launch_list_for_param(char * name, t_env * env, char ** reply, int fd_reply);

//channels_glob
void list_channels(t_env ** env);
void create_new_channel(char * channel_name);
int is_known_channel(char * channel_name);

//my_channels
void manage_join(t_env ** env);
void quit_channel(t_env ** env);
int pop_channel(char *, t_channel ** channel);

//utils
char * my_strcat(char *, char *);

//my_str_to_wordtab
char ** my_str_to_wordtab(char * str, char delim);
void launch_list_on_all(t_env * env, char ** reply, int fd_reply);

//message
void send_private_message(t_env ** env);

//tmp
void print_on_channel(char * channel_name, char * nickname, t_env *);

//verif
int is_channel(char *);
int is_nickname(char *, t_env *);

#endif
