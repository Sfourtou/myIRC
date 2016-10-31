/*
** main.c for  in /Users/fourto_s/Projects/Epitech/Tek2/IRC/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Fri May 20 23:00:54 2016 Sebastien Fourtou
** Last update Sun Jun  5 08:25:15 2016 Sebastien Fourtou
*/

#include "server.h"

void server_read(t_env ** env)
{
  printf("New client connection !\n");
  add_client(env);
}

void add_server(t_env *e)
{
  int s;
  struct sockaddr_in s_in;

  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
      exit(EXIT_SUCCESS);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(e->port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
      exit(EXIT_SUCCESS);
  if (listen(s, 42) == -1)
      exit(EXIT_SUCCESS);
  e->fd = s;
  e->fd_type = FD_SERVER;
  e->fct_read = server_read;
  e->fct_write = NULL;
  e->next = NULL;
  e->nickname = NULL;
  e->reply = NULL;
}

int launch_select(t_env * env)
{
  struct timeval tv;
  fd_set set_read;
  fd_set set_write;

  tv.tv_sec = 20;
  tv.tv_usec = 0;
  while (1)
    {
      init_set_fd(env, &set_read, &set_write);
      if (select(get_max_fd(env) + 1, &set_read, &set_write, NULL, &tv) == -1)
	{
	  perror("Select");
	  exit(EXIT_SUCCESS);
	}
      check_changes_fd(&env, &set_read, &set_write);
    }
}

void init_server(int port)
{
  t_env env;

  env.port = port;
  add_server(&env);
  launch_select(&env);
}

int main(int ac, char **av)
{
  if (ac < 2)
    {
      printf("./server [PORT]\n");
      return (1);
    }
  init_server(atoi(av[1]));
}
