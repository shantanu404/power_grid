#include "load.h"
#include "transmission.h"


void setup() {
  Serial.begin(9600);
  LoadInit(); // initializes internal calculations
  TransInit();
}

void loop() {
  LoadUpdate();
  TransUpdate();
  delay(500); // cut the board some slack
}
