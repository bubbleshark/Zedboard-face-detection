#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "image.h"

#define MYDEBUG

char* strrev(char* str)
{
  char *p1, *p2;
  if (!str || !*str)
  	return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
  {
  	*p1 ^= *p2;
  	*p2 ^= *p1;
  	*p1 ^= *p2;
  }
  return str;
}

void itochar(int x, char* szBuffer, int radix)
{
  int i = 0, n, xx;
  n = x;
  while (n > 0)
  {
  	xx = n%radix;
  	n = n/radix;
  	szBuffer[i++] = '0' + xx;
  }
  szBuffer[i] = '\0';
  strrev(szBuffer);
}

/* Writes a Pgm file using the hex image */
int writePgm(char *fileName, unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH] )
{
  char parameters_str[5];
  int i;
  FILE *fp = fopen(fileName, "wb");
  
  if (!fp){
    printf("Unable to open file %s\n", fileName);
    return -1;
  }
  
	fprintf(fp,"P5\n");
	fprintf(fp,"%d %d\n",IMAGE_WIDTH,IMAGE_HEIGHT);
	fprintf(fp,"%d\n",IMAGE_MAXGREY);
  
  for (i = 0; i < IMAGE_HEIGHT; i++) 
    for (int j = 0; j < IMAGE_WIDTH ; j++)
       fputc(Data[i][j], fp);
  
  fclose(fp);
  return 0;
}

/* draw white bounding boxes around detected faces */
void drawRectangle(unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH], MyRect r)
{
  int i;
  int col = IMAGE_WIDTH;
  //return;
  for (i = 0; i < r.width; i++)
    Data[r.y][r.x + i] = 255;
  for (i = 0; i < r.height; i++)
    Data[r.y+i][r.x + r.width] = 255;
  for (i = 0; i < r.width; i++)
    Data[r.y + r.height][r.x +i] = 255;
  for (i = 0; i < r.height; i++)
    Data[r.y + i][r.x] = 255;
}
