#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "launch.h"

bool launch(char **args)
{
  pid_t pid, wpid;
  int state;

  pid = fork();
  if(pid == 0)
  {
    // In child process, execvp overlays existing process
    if(execvp(args[0], args) == -1)
    {
      perror("command not found");
    }
    exit(EXIT_FAILURE);
  }
  else if(pid < 0)
  {
    perror("fork error");
  }
  else
  {
    do {
      wpid = waitpid(pid, &state, WUNTRACED);
    } while(!WIFEXITED(state) && !WIFSIGNALED(state));
  }
  return true;
}
