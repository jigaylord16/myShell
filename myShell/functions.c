#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

char *function_names[] = {
  "cd",
  "help",
  "quit"
};

int numFunctions()
{
  return sizeof(function_names)/sizeof(char *);
}

bool cd(char **args)
{
  if(args[1] == NULL)
  {
    perror("no directory entered");
  }
  else
  {
    if(chdir(args[1]) != 0)
    {
      perror("directory does not exist");
    }
  }
  return true;
}

bool help(char **args)
{
  int i;
  printf("Welcome to myShell\n");
  printf("Enter commands in the following format ");
  printf("[program name][argument 1][argument 2]...\n");
  printf("The following commands are built-in:\n");

  for(i = 0; i < numFunctions(); i++)
  {
    printf("\t%s\n", function_names[i]);
  }

  return true;
}

bool quit(char **args)
{
  return false;
}

bool (*functions[]) (char**) = {
  &cd,
  &help,
  &quit
};
