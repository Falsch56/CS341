/*Scott Fenton
* MP1
* 2/16/2017
*/


/******************************************************************
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
#include <stdlib.h> 
#include "slex.h"
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
PROTOTYPE int display_hex(char s[],char hex[], int hexpos);
/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD<addr>"},
	      {"ms",  mem_set,     "Memory set: MS<addr><value>"},
              {"s",   stop,        "Stop" },
	      {"h",   help,        "Help: H<command>"},
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

/*
*Convert the character string(arguments) to an integer - CHECK
*Use that integer as an address(a pointer to memory) - CHECK
*Find the contents of that address - CHECK
*Display the contents of that address to the terminal - CHECK
*/
int mem_display(Cmd *cp, char *arguments)
{
 unsigned int *y;
 unsigned int memcon, memcon1,memcon2,memcon3,number;
 char s[100],s1[100],s2[100],s3[100];
 char hexlist[100];
 int hexpos = 0,i = 0, gg, ggg;
 char temp[3];
 
 sscanf(arguments, "%x", &number); 

 y = number;//memory address of integer
 memcon = *y;
 memcon1 = *(y+1);
 memcon2 = *(y+2);
 memcon3 = *(y+3);
 sprintf(s, "%x", memcon);//convert integer to hex string
 sprintf(s1, "%x", memcon1);
 sprintf(s2, "%x", memcon2);
 sprintf(s3, "%x", memcon3);
 
 display_hex(s, hexlist, hexpos);
 hexpos += 12;
 display_hex(s1, hexlist, hexpos);
 hexpos += 12;
 display_hex(s2, hexlist, hexpos);
 hexpos += 12;
 display_hex(s3, hexlist, hexpos);

 printf("00%s   %s", arguments+1, hexlist);
 for(;i<=48;i=i+3){
   temp[0] = hexlist[i];
   temp[1] = hexlist[i+1];
   sscanf(temp, "%x", &gg);
   ggg = gg;
   if(gg > 32 && gg < 127)
   	printf("%c", ggg);
   else
	printf(".");
}
 printf("\n");
 
  return 0;			/* not done */
}

int display_hex(char s[], char hexlist[],int hexpos){
 int index = 0;
 int rem = 8;
 int space = 2;
 for(;s[index] != '\0'; index++)
   ;
 rem = rem - index;//remaining 0's to fill
 index--;
 //capture two at once
 for(;index >=0;index=index - 2,space=space-2){
   if(space == 0){
     //printf(" ");
     space = 2;
     hexlist[hexpos++] = ' ';
}  if(index == 0){
    //printf("0%c", s[index]);
    rem--;
    hexlist[hexpos++] = '0';
    hexlist[hexpos++] = s[index]; 
}
   else{
    //printf("%c%c", s[index-1],s[index]);
    hexlist[hexpos++] = s[index-1];
    hexlist[hexpos++] = s[index];
}
}
 for(;rem >0; rem--,space--){
  if(space == 0){
    //printf(" ");
    hexlist[hexpos++] = ' ';
    space = 2;}
  //printf("0");
  hexlist[hexpos++] = '0';
}
 //printf(" ");
 hexlist[hexpos++] = ' ';
 return 0;

}
//Set one byte in memory
int mem_set(Cmd *cp, char *arguments)
{
 unsigned int number, hexnnum, memcon;
 unsigned int *y;
 char s[100];
 char mem[] = {arguments[8],arguments[9]};
 char hexlist[100], temp[100];
 int hexpos = 0, i =10, g = 0;

 sscanf(arguments, "%x", &number);
 y = number;
 memcon = *y;
 sprintf(s, "%x", memcon);
 display_hex(s, hexlist, hexpos);
 		
 hexlist[0] = mem[0],hexlist[1] = mem[1];
 
 for(;i >=0; i=i-3,g=g+2){
        
	temp[g] = hexlist[i-1];
        temp[g+1] = hexlist[i];
        if(i == 1)
		break;
}
 
 sscanf(temp, "%x", &hexnnum);
 *y = hexnnum; 
 printf(" ");
 return 0;
}


//Complete and working
int help(Cmd *cp, char *arguments){
 
 if(arguments[0] == '\0')
	printf("Memory display:    MD <addr>\n"
	       "Memory set:        MS<addr><value>\n"
	       "Stop:              s\n"
	       "Help:              H<command>\n");
 else if(arguments[1] == 's' || arguments[1] == 'S')
	printf("Stop: s\n");
 else if(arguments[1] == 'm' && arguments[2] == 'd')
	printf("Memory display: MD<addr>\n");
 else if(arguments[1] == 'm' && arguments[2] == 's')
	printf("Memory set: MS<addr><value>\n");
 else
       printf("Invalid Command\n"); 

 return 0;
}
