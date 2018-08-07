/* accessible-ir-tx.ino
 *
 *    Firmware for Accessible infrared (IR) transmitter module
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */

#include <Wire.h>
#include "eeprom.h"
#include "parser.h"


#define bufferSize 25 

EeProm eeprom;
Parser parser;

String inStrg = "";         // incoming data

void setup() {
  Serial.begin(115200);
  while (!Serial); //delay for Leonardo
  parser.sendIDN();
  inStrg.reserve(bufferSize+2);
  Wire.begin(5);
  Wire.onReceive(receiveEvent);

}


void loop() {
    int serialByte = Serial.read();
    if (serialByte != -1) {
        char inChar = (char)serialByte;

        if ((inChar == '\n') || (inChar == '\r') || (inChar == ';')) {
            inStrg.trim();
            inStrg.toUpperCase();
            parser.command(inStrg);
            inStrg ="";

        } else {

            inStrg += inChar;
            if (inStrg.length() >= bufferSize) inStrg ="";

        }
    }
}

void receiveEvent(int howMany)
{
  while(Wire.available())
  {
    char inChar = (char)Wire.read();

    if ((inChar == '\n') || (inChar == '\r') || (inChar == ';')) {
        inStrg.trim();
        inStrg.toUpperCase();
        parser.command(inStrg);
        inStrg ="";

    } else {

        inStrg += inChar;
        if (inStrg.length() >= bufferSize) inStrg ="";

    }
  }
}

