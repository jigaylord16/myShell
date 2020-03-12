#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern char *function_names[3];

int numFunctions();
bool cd(char **args);
bool help(char **args);
bool quit(char **args);

extern bool (*functions[]) (char**);

#endif
