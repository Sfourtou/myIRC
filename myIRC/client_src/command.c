/*
** command.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/client
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sat May 21 18:24:35 2016 Sebastien Fourtou
** Last update Tue Jun  7 13:29:38 2016 Sebastien Fourtou
*/

#include "client.h"

char * get_command(char * buffer)
{
  char first[20];
  int i;

  i = -1;
  while (buffer[++i] && buffer[i] != ' ')
    first[i] = buffer[i];
  first[i] = 0;
  return (strdup(first));
}

int is_command(char * command, t_fct fct)
{
  int i;

  i = 0;
  while (fct.commands[i])
    {
      if (strcmp(command, fct.commands[i]) == 0)
	return (i);
      ++i;
    }
  return (-1);
}

void exec_command(int idx, t_client * client)
{
  (*client->fct.fct_ptr[idx])(client);
}
