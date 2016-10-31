/*
** client-server.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sat May 21 18:06:26 2016 Sebastien Fourtou
** Last update Tue Jun  7 13:28:52 2016 Sebastien Fourtou
*/

#include "client.h"

void send_server(int cs, t_client * client)
{
  if (client->buffer_cin != NULL)
    {
      write(cs, client->buffer_cin, strlen(client->buffer_cin));
      if (strcmp(client->buffer_cin, "QUIT") == 0)
	{
	  close(cs);
	  free(client->buffer_cin);
	  exit(EXIT_SUCCESS);
	}
      free(client->buffer_cin);
      client->buffer_cin = NULL;
    }
}

void read_server(int cs, t_client * client)
{
  int r;
  char buffer[4096];

  if ((r = read(cs, buffer, 4096)) > 0)
    {
      buffer[r] = 0;
      client->buffer_server = strdup(buffer);
    }
  return;
}

void prepare_connect_server(t_client * client)
{
  char * command[2];

  command[0] = strtok(client->buffer_cin, " ");
  command[1] = strtok(NULL, " ");
  if (command[1] == NULL)
    {
      printf("Invalid command /server\n");
      return;
     }
  connect_server(client, atoi(command[1]));
  return;
}

int connect_server(t_client * client, int port)
{
  struct sockaddr_in sin;

  if ((client->client_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("Socket");
      return (-1);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (connect(client->client_socket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      perror("Connect");
      return (-1);
    }
  free(client->buffer_cin);
  client->buffer_cin = NULL;
  client->is_connected = 1;
  client->nickname = "Anonymous";
  return (0);
}
