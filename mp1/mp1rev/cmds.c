/*
*Scott Fenton
*MP1
*2/20/2017
*/




/********************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     ?
*
*   semantic actions for commands called by tutor (cs341, hw2)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"
#include <stdlib.h>
#pragma GCC diagnostic ignored "-Wint-conversion"
/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);
 
/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
	      {"ms",  mem_set,	   "Memory set: MS <addr><addr>"},
	      {"h",   help,	   "Help: H"},
              {"s",   stop,        "Stop" },
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments)
{
  return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/

int mem_display(Cmd *cp, char *arguments)
{
  unsigned char *y;
  unsigned int memadd;
  int i;  
  char dot[100];
  int temp;

  sscanf(arguments, "%x", &memadd);//hex value of argument
  y = memadd;

  printf("%08d   ", atoi(arguments));
  for(i=0;i < 16;i++){
	printf("%02x ",*(y++));
        temp = (int) *y;
        if(temp > 32 && temp < 127)
		dot[i] = (char) *y;
	else
		dot[i] = '.';
  }
  printf("%s\n", dot);
  return 0;			/* not done */
}

int mem_set(Cmd *cp, char *arguments){
  unsigned char *y;
  unsigned int memcng;
  int i = 1;
  int index = 0;
  char arg[100];
  int bol = 0;

  for(;arguments[i] != '\0';i++){
	if(arguments[i] == ' ')
		bol = 1;
	if(bol == 1){
		arg[index] = arguments[i];
		index++;}
}
	
  sscanf(arguments, "%x", &memcng);
  sscanf(arg, "%x", &i);
  y = memcng;
  *y = i;
 
  return 0;
}


int help(Cmd *cp, char *arguments){
  char arg[10] = {arguments[1], arguments[2]};   
  int pos;
  int newpos;

  if(arg[0] == 'm' && arg[1] == 'd'){
	slex(arg, cmds, &pos, &newpos);
        printf("%d   %d", pos, newpos);
  }
  else
   	printf("     cmd    help message\n");
   	for(cp = cmds; cp->cmdtoken; cp++) 
      	    printf("%8s    %s\n", cp->cmdtoken, cp->help);

  return 0;
}
