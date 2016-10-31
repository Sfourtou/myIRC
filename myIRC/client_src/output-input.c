/*
** output-input.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sat May 21 18:06:12 2016 Sebastien Fourtou
** Last update Sun Jun  5 09:00:03 2016 Sebastien Fourtou
*/

#include "client.h"

void connect_first(t_client * client)
{
  printf("Not connected : please use 'server'\n");
  free(client->buffer_cin);
  client->buffer_cin = NULL;
}

void check_command(t_client * client, int idx)
{
  if (client->buffer_cin[0] == '/')
    {
      if ((idx = is_command(get_command(client->buffer_cin), client->fct)) != -1)
	{
	  if (idx > 1 && client->is_connected != 1)
	    {
	      connect_first(client);
	      return;
	    }
	  exec_command(idx, client);
	  return;
	}
      if (client->is_connected != 1)
	{
	  connect_first(client);
	  return;
	}
      return;
    }
  if (client->is_connected != 1)
    {
      connect_first(client);
      return;
    }
}

void read_input(t_client * client)
{
  int r;
  char buffer[4096];

  if ((r = read(0, buffer, 4096)) > 0)
    {
      if (r > 1)
	buffer[r - 1] = 0;
      client->buffer_cin = strdup(buffer);
      check_command(client, 0);
    }
  return;
}

void write_client(t_client * client)
{
  if (client->buffer_server != NULL)
    {
      printf("%s", client->buffer_server);
      free(client->buffer_server);
      client->buffer_server = NULL;
    }
}
