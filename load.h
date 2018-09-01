#ifndef _load_h
#define _load_h

#include "Arduino.h"
#include "SoftwareSerial.h"

#define LOAD_START 8
#define LOAD_END   12
#define LOAD_SIZE  (LOAD_END - LOAD_START + 1)

#define LOAD_RESISTANCE 1000.0
#define LOAD_VOLTAGE 5.0
#define POWER_PER_LOAD ((LOAD_VOLTAGE * LOAD_VOLTAGE) / LOAD_RESISTANCE)

#define GetCurrentUsage() (ActiveLoads() * POWER_PER_LOAD)

static bool load_taken[LOAD_SIZE] = { false };

/* Initializes the pins and get serial ready (on debug) */
void LoadInit() {
  //TODO: remove this on demo
  Serial.begin(9600);
  Serial.println("Initializing pins....");
  
  for (int x = LOAD_START; x <= LOAD_END; x ++) {
    pinMode(x, INPUT);
  }

  Serial.println("Initialization complete!");
}

/* returns the number of loads present in the circuit printing them to serial in process (on debug)*/
const static int ActiveLoads() {
  int rc = 0;
  for (int x = 0; x < LOAD_SIZE; x ++) {
    if (load_taken[x]) {
      //TODO: remove this on demo
      Serial.println(x);
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

  //TODO: remove on demo
  Serial.print(ActiveLoads());
  Serial.println(" are active!");
  Serial.print(GetCurrentUsage());
  Serial.println(" Watts is in use!");
}

#endif
