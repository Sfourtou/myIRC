/*
** utils.c for PSU_2015_myirc in /Users/fourto_s/Projects/Epitech/Tek2/PSU_2015_myirc/server
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Tue May 24 14:41:53 2016 Sebastien Fourtou
** Last update Tue May 24 14:47:17 2016 Sebastien Fourtou
*/

#include "server.h"

char *my_strcat(char *s1, char * s2)
{
  char * tmp;

  if ((tmp = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))) == NULL)
    return (NULL);
  strcpy(tmp, s1);
  s1 = strcat(tmp, s2);
  return (s1);
}
