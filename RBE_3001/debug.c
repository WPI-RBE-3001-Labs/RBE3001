/*
 * debug.c
 *
 *  Created on: Jan 25, 2017
 *      Author: vargoal
 */

#include "RBELib/RBELib.h"

static FILE outputFile = FDEV_SETUP_STREAM(printfRBE, NULL, _FDEV_SETUP_WRITE);


int printfRBE(char var, FILE *stream) {
  putCharDebug(var);
  return 0;
}

void initRBELib(){
  stdout = &outputFile;
  debugUSARTInit(115200);
}
