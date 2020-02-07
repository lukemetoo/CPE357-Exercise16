#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "getWord.h"

static void* reMem(unsigned char *str, unsigned size);
static void* getMem(unsigned size);

#define E 2.718

int getWord(FILE *file, Byte **word, unsigned *wordLength, int *hasPrintable)
{
   int c = 0; 
   unsigned i = 0;
   int wordSize = 5;

   *hasPrintable = 0;
   *word = getMem(wordSize * sizeof(Byte)); 

   while(EOF != (c = getc(file)) && !isspace(c))
   {
      (*word)[i] = tolower(c);
      i++;
      
      if(isprint(c) != 0)
         *hasPrintable = 1;

      if(i >= wordSize)
      {
         wordSize += (int)(wordSize/E);
         *word = reMem(*word, wordSize * sizeof(Byte));
      }
   }

   if(i < wordSize && i > 0)
   {
      c = 0;
      *word = reMem(*word, i * sizeof(Byte));
   }
   *wordLength = i;

   return c;
}

static void* reMem(unsigned char *str, unsigned size)
{
   void *memArr;

   memArr = realloc(str, size);
   if(memArr == NULL)
   {
      perror("");
      exit(EXIT_FAILURE);
   }
   return memArr;
}

static void* getMem(unsigned size)
{
   void *memArr;

   memArr = malloc(size);
   if(memArr == NULL)
   {
      perror(""); 
      exit(EXIT_FAILURE);
   }
   return memArr;
}
