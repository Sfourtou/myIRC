/*
** command.c for myIRC in /Users/fourto_s/Projects/Epitech/Tek2/myIRC/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Sun May 22 12:29:22 2016 Sebastien Fourtou
** Last update Wed May 25 19:53:25 2016 Sebastien Fourtou
*/

#include "server.h"

void quit_all(t_env **env)
{
  dprintf((*env)->fd, "QUIT: Client has quit\r\n");
  close((*env)->fd);
  (*env)->fd_type = FD_FREE;
}

t_fct init_command()
{
  t_fct fct;

  fct.commands[0] = "NICK";
  fct.commands[1] = "JOIN";
  fct.commands[2] = "LIST";
  fct.commands[3] = "USERS";
  fct.commands[4] = "NAMES";
  fct.commands[5] = "PART";
  fct.commands[6] = "QUIT";
  fct.commands[7] = "PRIVMSG";
  fct.commands[8] = NULL;
  fct.fct_ptr[0] = &change_nickname;
  fct.fct_ptr[1] = &manage_join;
  fct.fct_ptr[2] = &list_channels;
  fct.fct_ptr[3] = &list_users;
  fct.fct_ptr[4] = &list_users_channel;
  fct.fct_ptr[5] = &quit_channel;
  fct.fct_ptr[6] = &quit_all;
  fct.fct_ptr[7] = &send_private_message;
  return fct;
}

int do_command(t_env ** env)
{
  int i;
  t_fct fct;
  char buffer[20];

  i = -1;
  while ((*env)->last_message[++i] && (*env)->last_message[i] != ' ')
    buffer[i] = (*env)->last_message[i];
  buffer[i] = 0;
  i = -1;
  fct = (*env)->fct;
  while (fct.commands[++i])
    {
      if (strcmp(buffer, fct.commands[i]) == 0)
	{
	  printf("%s : %s\n", (*env)->nickname, (*env)->last_message);
	  (*fct.fct_ptr[i])(env);
	  return (0);
	}
    }
  return (1);
}
