/*
** main.c for  in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sat May 21 02:52:48 2016 Sebastien Fourtou
** Last update Tue Jun  7 13:34:29 2016 Sebastien Fourtou
*/

#include "client.h"

void my_quit(t_client * client)
{
  asprintf(&client->buffer_cin, "QUIT");
}

void init_fct_ptr(t_client * client)
{
  client->fct.commands[0] = "/server";
  client->fct.commands[1] = "/nick";
  client->fct.commands[2] = "/join";
  client->fct.commands[3] = "/list";
  client->fct.commands[4] = "/users";
  client->fct.commands[5] = "/names";
  client->fct.commands[6] = "/part";
  client->fct.commands[7] = "/msg";
  client->fct.commands[8] = "/quit";
  client->fct.commands[9] = NULL;
  client->fct.fct_ptr[0] = &prepare_connect_server;
  client->fct.fct_ptr[1] = &change_nickname;
  client->fct.fct_ptr[2] = &join_channel;
  client->fct.fct_ptr[3] = &list_channel;
  client->fct.fct_ptr[4] = &list_users;
  client->fct.fct_ptr[5] = &list_users_channel;
  client->fct.fct_ptr[6] = &quit_channel;
  client->fct.fct_ptr[7] = &manage_messages;
  client->fct.fct_ptr[8] = &my_quit;
}

void launch_select(t_client * client)
{
  struct timeval tv;
  fd_set set_read;
  fd_set set_write;

  tv.tv_sec = 20;
  tv.tv_usec = 0;
  while (1)
    {
      init_my_sockets(&set_read, &set_write, client->client_socket);
      if (select(4, &set_read, &set_write, NULL, &tv) == -1)
	perror("Select");
      if (FD_ISSET(0, &set_read))
	read_input(client);
      if (FD_ISSET(1, &set_write))
	write_client(client);
      if (FD_ISSET(client->client_socket, &set_write))
	send_server(client->client_socket, client);
      if (FD_ISSET(client->client_socket, &set_read))
	read_server(client->client_socket, client);
    }
}

void launch_first_read(t_client * client)
{
  while (client->is_connected == 0)
    {
      read_input(client);
      free(client->buffer_cin);
      client->buffer_cin = NULL;
    }
  launch_select(client);
}

void init_client()
{
  t_client client;

  client.buffer_cin = NULL;
  client.buffer_server = NULL;
  client.is_connected = 0;
  init_fct_ptr(&client);
  launch_first_read(&client);
}

int main()
{
  init_client();
}
