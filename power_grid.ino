 #include "load.h"

void setup() {
  LoadInit(); // initializes internal calculations
}

void loop() {
  LoadUpdate(); // calculating
  delay(2000); // cut the board some slack
}
