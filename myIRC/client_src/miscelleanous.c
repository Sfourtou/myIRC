/*
** miscelleanous.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun May 22 12:15:10 2016 Sebastien Fourtou
** Last update Wed May 25 00:55:20 2016 Sebastien Fourtou
*/

#include "client.h"

void change_nickname(t_client * client)
{
  char * part[2];
  char tmp[strlen(client->buffer_cin)];

  strcpy(tmp, client->buffer_cin);
  part[0] = strtok(tmp, " ");
  part[1] = strtok(NULL, " ");
  if (part[1] == NULL)
    {
      asprintf(&client->buffer_cin, "NICK");
      return;
    }
  asprintf(&client->buffer_cin, "NICK %s", part[1]);
}

void list_users(t_client * client)
{
  asprintf(&client->buffer_cin, "USERS");
}

void list_users_channel(t_client * client)
{
  char * param;

  strtok(client->buffer_cin, " ");
  param = strtok(NULL, " ");
  if (param == NULL)
    {
      asprintf(&client->buffer_cin, "NAMES");
      return;
    }
  asprintf(&client->buffer_cin, "NAMES %s", param);
}
