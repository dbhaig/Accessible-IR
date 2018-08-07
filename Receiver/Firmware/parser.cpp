/* parser.cpp
 *
 *    Command parser class to process command strings
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */

#include <Arduino.h>
//#include "eeprom.h"
#include "parser.h"
//#include "transmitter.h"                                                                                                                          

//extern EeProm eeprom;

//Transmitter irtx;   

Parser::Parser() {
}

void Parser::_printPrgMemStr(const byte PROGMEM *str) {
    // From Arduino Cookbook with updates
    char c;

    while (( c = pgm_read_byte(str++))) Serial.write(c);
}


void Parser::sendIDN() {
    _printPrgMemStr(idn_msg);
}

int Parser::_getCommandIndex(String str) {
    int i=0;

    if (str.indexOf(' ') > 0)   // truncate after space if present
        str.remove(str.indexOf(' '));

    while (i < _cmdCnt) {
        if (commands[i] == str) {
            return i;
        }
        i++;        
    }

    return i;

}


String Parser::_removeBeforeSpace(String str) {
    if (str.indexOf(' ') > 0) {
        str = str.substring(str.indexOf(' ')+1);
        return str;
    }
    else {
        return "";
    }
}


String Parser::_removeAfterSpace(String str) {
    if (str.indexOf(' ') > 0) {
        str = str.substring(0, str.indexOf(' '));
        return str;
    }
    else {
        return str;
    }
}


String Parser::_getFirstParameter(String str) {
    str = _removeBeforeSpace(str);
    str = _removeAfterSpace(str);
    return str;
}


String Parser::_getSecondParameter(String str) {
    str = _removeBeforeSpace(str);
    str = _removeBeforeSpace(str);
    str = _removeAfterSpace(str);
    return str;
}


bool Parser::_hasHexPrefix(String str) {
    if (str.length() < 2 ) return false;
    if (str[0] != '0' ) return false;
    if (str[1] != 'X' ) return false;
    return true;
}


int Parser::_getFirstInt(String str) {
    str = _getFirstParameter(str);
    if (str.length() == 0 ) return 0;  // default if no parameter present
    if (str.length() > 3) return -1;
    return str.toInt();
}


int Parser::_getSecondInt(String str) {
    str = _getSecondParameter(str);
    if (str.length() == 0 || str.length() > 3) return -1;
    return str.toInt();
}


int Parser::_hexToInt(String str) {
    float d = 0;      // digit value
    float result = 0;

    for (int i = 0; i < str.length(); i++) {
       d = str[i] - '0';
       if (d > 15) d = d - 7;  // For Digits A-F
       result = result + d*(pow(16,str.length()-i-1));
    }

    return round(result);

}


//int Parser::_getEepromHexAddr(String str) {
//    float d = 0;      // digit value
//    float result = 0;
//
//    str = _getFirstParameter(str);
//    if (!_hasHexPrefix(str)) return -1;
//    str = str.substring(2);
//    if (str.length() > 3) return -1;
//
//    for (int i = 0 ; i < str.length() ; i++) {
//        if (!isHexadecimalDigit(str[i])) return -1;
//    }
//
//    if (_hexToInt(str) > EE_LAST_ADDR) return -1;
//
//    return _hexToInt(str);
//}


void Parser::_echoCommand(int command_num, int param) {

    Serial.print(commands[command_num]);
    Serial.print(" ");
    Serial.println(param);
}


//void Parser::_outputHexBytes(String inStrg, int byte_count) {
//    
//    Serial.print("0X");
//    for (int i = byte_count - 1; i >= 0; i--) { 
//        if (eeprom.read_byte(_getEepromHexAddr(inStrg)+i) < 16) Serial.print('0');
//        Serial.print(eeprom.read_byte(_getEepromHexAddr(inStrg)+i), HEX);
//    }
//    Serial.println();
//}


void Parser::command(String inStrg) {
    int i=0;
    int param_1;
    int param_2;

    //Serial.println("Processing Command: '" + inStrg + "'");

    switch(_getCommandIndex(inStrg)) {

        case 0: // '?'
          _printPrgMemStr(star_msg);
          _printPrgMemStr(help_msg);
          _printPrgMemStr(star_msg);
          break; 

        case 1: // '*IDN?'
          sendIDN();
          break; 

        default:
          // Ignore invalid commands
          return;
    }
}
