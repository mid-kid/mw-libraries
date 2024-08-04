/*****************************************************
   embedded.c - Embedded functions
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

/* this module implements functions not available on
   an embedded target. It replaces those functionality
   with some functionality of the simulator.
   
   printf => redirection to simulation terminal
   scanf  => redirection to simulation terminal
 */
   
#include <ansi_parms.h>

#if _MSL_C_TINY_IO
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <console_io.h>


char* gets(char* s) {
/* The gets() function reads a line from the standard input stream stdin and stores it in buffer s.
   The line consists of all characters up to and including the first newline character ('\n').
   gets() then replaces the newline character with a null character ('\0') before returning
   the line. In contrast, the fgets function retains the newline character. */
  unsigned char ch;
  char* p = (char *)s;
  
  do {
    ch = TERMIO_GetChar();
    *p++ = ch; 
  } while(ch != '\n' && ch != '\r');
  *(p-1) = '\0'; /* replace '\n' with '\0' */
  return (char *)s;
}

int puts(const char* s) {
  /* The puts() function writes string to the standard output stream stdout,
     replacing the string’s terminating null character ('\0') with a newline character ('\n')
     in the output stream.
     returns a nonnegative value if successful. If puts fails it returns EOF */
  unsigned long cnt = strlen(s);
  __write_console(1, (unsigned char *)s, &cnt, 0L);
  TERMIO_PutChar('\n');
  return 1; /* success */
}
/*-----------------------------------------------------------------*/
/* file I/O */
/* for file I/O we are using the terminal functionality and writing
   to a file. Note that this is limited to one active file only! */

int fflush(FILE *stream) {
/*  TERMIO_PutChar('\n'); no buffering */
  return 0;
}

int fprintf(FILE *f, const char* format, ...) {
  int i;
  va_list args;
  
  set_printf(TERMIO_PutChar); /* set up TERMIO_PutChar for writing */
  va_start(args, format);
  i = vprintf(format, args);
  va_end(args);
  return i;
}

int fputc(int c, FILE *f) {
  TERMIO_PutChar((char)c);
  return 0; /* ok */
}
/*
int setvbuf(FILE *f, char *b, int m, size_t s) { return 0; }
*/
#endif /*_MSL_C_TINY_IO  */