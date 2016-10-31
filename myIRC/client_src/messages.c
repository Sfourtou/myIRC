/*
** messages.c for PSU_2015_myirc in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Wed May 25 00:45:21 2016 Sebastien Fourtou
** Last update Tue Jun  7 13:19:33 2016 Sebastien Fourtou
*/

#include "client.h"

void manage_messages(t_client * client)
{
  char * param1;
  char * param2;

  strtok(client->buffer_cin, " ");
  param1 = strtok(NULL, " ");
  param2 = strtok(NULL, "");
  if (param1 == NULL)
    {
      asprintf(&client->buffer_cin, "PRIVMSG");
      return ;
    }
  else if (param2 == NULL)
    {
      asprintf(&client->buffer_cin, "PRIVMSG %s", param1);
      return ;
    }
  else
    {
      asprintf(&client->buffer_cin, "PRIVMSG %s %s", param1, param2);
      return ;
    }
}
