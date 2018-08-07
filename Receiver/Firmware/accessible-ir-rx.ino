/* accessible-ir-rx.ino
*
*    Firmware for Accessible infrared (IR) receiver module
*
*    Copyright 2018 Don Haig (time4tux at gmail dot com)
*
*    GNU GPLv3 (See LICENSE for details)·
*
*/

#include <IRLibDecodeBase.h>
#include <IRLib_P01_NEC.h>    //Lowest numbered protocol 1st
#include <IRLib_P02_Sony.h>
#include <IRLib_P03_RC5.h>
#include <IRLib_P04_RC6.h>
#include <IRLib_P05_Panasonic_Old.h>
#include <IRLib_P06_JVC.h>
#include <IRLib_P07_NECx.h>
#include <IRLib_P08_Samsung36.h>
#include <IRLib_P09_GICable.h>
#include <IRLib_P10_DirecTV.h>
#include <IRLib_P11_RCMM.h>
#include <IRLibCombo.h>       // After all protocols, include this
#include <IRLibRecvPCI.h>

#include "parser.h"

#define bufferSize 15

IRdecode myDecoder;
Parser parser;


IRrecvPCI myReceiver(2); //pin number for the receiver

// Storage for the recorded code
uint8_t codeProtocol;  // The type of code
uint32_t codeValue;    // The data bits if type is not raw
uint8_t codeBits;      // The length of the code in bits

//These flags keep track of whether we received the first code 
//and if we have have received a new different code from a previous one.
bool gotOne, gotNew; 

void setup() {
  gotOne=false; gotNew=false;
  codeProtocol=UNKNOWN; 
  codeValue=0; 
  Serial.begin(115200);
  delay(2000);while(!Serial);//delay for Leonardo
  parser.sendIDN(); 
  Serial.println(F("ir_receiver:"));
  myReceiver.enableIRIn(); // Start the receiver
}

// Stores the code for later playback
void storeCode(void) {
  gotNew=true;    gotOne=true;
  codeProtocol = myDecoder.protocolNum;
  Serial.print(F("Received "));
  Serial.print(Pnames(codeProtocol));
  if (codeProtocol==UNKNOWN) {
    Serial.println(F(" - Protocol Unknown!"));
  }
  else {
    if (myDecoder.value == REPEAT_CODE) {
      // Don't record a NEC repeat value as that's useless.
      Serial.println(F("repeat; ignoring."));
    } else {
      codeValue = myDecoder.value;
      codeBits = myDecoder.bits;
    }
    Serial.print(F(" Value:0x"));
    Serial.println(codeValue, HEX);
  }
}

void loop() {
  if (myReceiver.getResults()) {
    myDecoder.decode();
    storeCode();
    myReceiver.enableIRIn(); // Re-enable receiver
  }
}

