#ifndef _transmission_h
#define _transmission_h

#include "SoftwareSerial.h"
#include "load.h"

#define RX 11
#define TX 10

#define ID 2
#define gatePin 12

int history[10];
static SoftwareSerial arduino_serial(11, 10);

void send(const char* data) {
  if (!arduino_serial.available()) {
    //Serial.println("YEYE");
    for (int i = 0; i < 4; i ++) {
      arduino_serial.print(data[i]);
    }
  }
}

bool recv(char* data) {
  if (arduino_serial.available()) {

    byte i = 0;
    while (arduino_serial.available()) {
      //Serial.print("stub!");
      data[i++] = arduino_serial.read();
    }
    return true;;
  }
  return false;
}

void TransInit() {
  memset(history, -1, sizeof(history));
  Serial.begin(57600);
  arduino_serial.begin(9600);
}

void TransUpdate() {
  
  char data[10];

  int prev, root, dist, load;

  //digitalWrite(gatePin, LOW);

  int diff = LoadDiff();
  if (diff < 0) {
    Serial.println(diff);
    data[0] = ID;
    data[1] = ID;
    data[2] = 0;
    data[3] = -diff;
    send(data);
    return;
  }

  if (recv(data)) {
    Serial.print((unsigned)data[0]);
    Serial.print("\t");
    Serial.print((unsigned)data[1]);
    Serial.print("\t");
    Serial.print((unsigned)data[2]);
    Serial.print("\t");
    Serial.print((unsigned)data[3]);
    Serial.print("\n");

    if(data[1] == ID){
      digitalWrite(gatePin, LOW);
      return;
    }
    
    if (dist == 0 && load == 0 && data[0] == (1 << 8) - 1) {
      if (history[data[1]] == -1) {
        digitalWrite(gatePin, LOW);
        return;
      } else {
        digitalWrite(gatePin, HIGH);
        if(ID == data[1]){
          return;
        }
        send(data);
        return;
      }
    }

    //Serial.println("no return");
    prev = data[0];
    root = data[1];
    dist = data[2];
    load = data[3];
    
    int extra = LoadDiff();
    Serial.println(extra);
    if (extra < load) {
      load -= extra;
      data[0] = ID;
      data[1] = root;
      data[2] = dist + 1;
      data[3] = load;
      history[root] = prev;
      send(data);
      return;
    } else {
      digitalWrite(gatePin, HIGH);
      load = 0;
      data[0] = (1<<8) - 1;
      data[1] = root;
      data[2] = 0;
      data[3] = 0;
      send(data);
      return;
    }

    if (load == 0) {
      return;
    }
  }
}

#endif
