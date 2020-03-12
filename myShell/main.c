#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "launch.h"
#include "functions.h"

/*
 * Execute user commands, if command is built in respective function is called
 * if not, launch is called passing args.
 */
bool execute(char **args)
{
  int i;

  if(!args)
  {
    return true;
  }

  for(i = 0; i < numFunctions(); i++)
  {
    if(strcmp(args[0], function_names[i]) == 0)
    {
      return(*functions[i])(args);
    }
  }
  return launch(args);
}

/*
 * Parse user input by allocating memory to args list and fill with tokenized
 * input, checking to see if the buffer has been exceeded and returning args.
 */
char **parseInput(char *input)
{
  int size = strlen(input);
  int index = 0;
  char **args = malloc(size * sizeof(char*));
  char *arg;
  //Check if args is null
  if(!args)
  {
    perror("allocation error");
    exit(EXIT_FAILURE);
  }
  //Split input by whitespace delimiters
  arg = strtok(input, " \t\r\n\a");
  while(arg != NULL)
  {
    args[index] = arg;
    index++;
    //Check if buffer is full to reallocate memory if necessary
    if(index >= size)
    {
      size += size;
      args = realloc(args, size * sizeof(char*));
      if(!args)
      {
        perror("reallocation failure");
        exit(EXIT_FAILURE);
      }
    }
    arg = strtok(NULL, " \t\r\n\a");
  }
  args[index] = NULL;
  return args;
}

/*
 * Read user input and return a pointer to input.
 */
char *readInput(void)
{
  char *input = NULL;
  size_t size = 0;
  getline(&input, &size, stdin);
  return input;
}


/*
 * The main function where user input, the argument list, and the bool value
 * that controls the do-while loop. User in prompted and then input is read
 * parsed and executed.
 */
int main()
{
  //Declarations of input line, list of args, status boolean
  char *input;
  char **args;
  bool state;
  //Do-while loop that prompts, reads, parses, and executes
  do {
    printf("%s> ", getenv("USER"));
    input = readInput();
    args = parseInput(input);
    state = execute(args);
    //Free input and args after command has been executed
    free(input);
    free(args);
  } while(state);
  return EXIT_SUCCESS;
}
