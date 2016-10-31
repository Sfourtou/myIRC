/*
** channels.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Mon May 23 00:21:58 2016 Sebastien Fourtou
** Last update Tue May 24 15:15:11 2016 Sebastien Fourtou
*/

#include "client.h"

void join_channel(t_client * client)
{
  char * param;

  strtok(client->buffer_cin, " ");
  param = strtok(NULL, " ");
  if (param == NULL)
    {
      asprintf(&client->buffer_cin, "JOIN");
      return;
    }
  asprintf(&client->buffer_cin, "JOIN %s", param);
}

void list_channel(t_client * client)
{
  char * param;

  strtok(client->buffer_cin, " ");
  param = strtok(NULL, " ");
  if (param == NULL)
    {
      asprintf(&client->buffer_cin, "LIST");
      return;
    }
  asprintf(&client->buffer_cin, "LIST %s", param);
}

void quit_channel(t_client * client)
{
  char * param;

  strtok(client->buffer_cin, " ");
  param = strtok(NULL, " ");
  if (param == NULL)
    {
      asprintf(&client->buffer_cin, "PART");
      return;
    }
  asprintf(&client->buffer_cin, "PART %s", param);
}
