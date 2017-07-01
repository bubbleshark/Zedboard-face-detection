#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "haar.h"

#ifdef __cplusplus
extern "C" {
#endif

void drawRectangle ( unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH], 
                     MyRect r);

int writePgm(char *fileName, unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH] );

#ifdef __cplusplus
}
#endif

#endif
