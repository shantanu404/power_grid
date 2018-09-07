#ifndef _generator_h
#define _generator_h

#include "load.h"

#define GEN_START 5
#define GEN_END 8
#define GEN_SIZE (GEN_END - GEN_START + 1)
#define GEN_VOLT 9.0

#define GetCurrentVoltage() (ActiveGens() * GEN_VOLT)

static bool gen_on[GEN_SIZE] = { false };

void GenInit() {  
  for (int x = GEN_START; x <= GEN_END; x ++) {
    pinMode(x, INPUT);
  }
}

const static int ActiveGens() {
  int rc = 0;
  for (int x = 0; x < GEN_SIZE; x ++) {
    if (gen_on[x]) {
      rc ++;
    }
  }

  return rc;
}

void GenUpdate() {
  for (int x = 0; x < GEN_SIZE; x ++) {
    gen_on[x] = digitalRead(x + GEN_START);
  }
}

#endif

