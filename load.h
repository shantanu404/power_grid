#ifndef _load_h
#define _load_h

#define LOAD_START 7
#define LOAD_END   9
#define LOAD_SIZE  (LOAD_END - LOAD_START + 1)

#define OPT_LOAD 2

static bool load_taken[LOAD_SIZE] = { false };

/* Initializes the pins and get serial ready (on debug) */
void LoadInit() {
  Serial.begin(57600);
  for (int x = LOAD_START; x <= LOAD_END; x ++) {
    pinMode(x, INPUT);
  }
}

/* returns the number of loads present in the circuit printing them to serial in process (on debug)*/
const static int ActiveLoads() {
  int rc = 0;
  for (int x = 0; x < LOAD_SIZE; x ++) {
    if (load_taken[x]) {
      //Serial.println(x);
      rc ++;
    }
  }

  return rc;
}

/* gets the current circuit state of the board and refreshes internal memory of them */
void LoadUpdate() {
  for (int x = 0; x < LOAD_SIZE; x ++) {
    load_taken[x] = digitalRead(x + LOAD_START);
  }
}

int LoadDiff() {
  return OPT_LOAD - ActiveLoads();
}


#endif
