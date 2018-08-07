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
#include "eeprom.h"
#include "parser.h"
#include "transmitter.h"                                                                                                                          

extern EeProm eeprom;

Transmitter irtx;   

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


int Parser::_getEepromHexAddr(String str) {
    float d = 0;      // digit value
    float result = 0;

    str = _getFirstParameter(str);
    if (!_hasHexPrefix(str)) return -1;
    str = str.substring(2);
    if (str.length() > 3) return -1;

    for (int i = 0 ; i < str.length() ; i++) {
        if (!isHexadecimalDigit(str[i])) return -1;
    }

    if (_hexToInt(str) > EE_LAST_ADDR) return -1;

    return _hexToInt(str);
}


void Parser::_echoCommand(int command_num, int param) {

    Serial.print(commands[command_num]);
    Serial.print(" ");
    Serial.println(param);
}


void Parser::_outputHexBytes(String inStrg, int byte_count) {
    
    Serial.print("0X");
    for (int i = byte_count - 1; i >= 0; i--) { 
        if (eeprom.read_byte(_getEepromHexAddr(inStrg)+i) < 16) Serial.print('0');
        Serial.print(eeprom.read_byte(_getEepromHexAddr(inStrg)+i), HEX);
    }
    Serial.println();
}


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

        case 2: // 'P'
          if (irtx.powerOnOff()) Serial.println(commands[2]);
          break; 

        case 3: // 'VUP'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxVolRpts) {
            if (irtx.volumeUp(param_1)) {
                _echoCommand(3, param_1);
            }
          }
          break; 

        case 4: // 'VDN'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxVolRpts) {
            if (irtx.volumeDown(param_1)) {
                _echoCommand(4, param_1);
            }
          }
          break; 

        case 5: // 'CUP'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxChnRpts) {
            if (irtx.channelUp(param_1)) {
                _echoCommand(5, param_1);
            }
          }
          break; 

        case 6: // 'CDN'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxChnRpts) {
            if (irtx.channelDown(param_1)) {
                _echoCommand(6, param_1);
            }
          }
          break; 

        case 7: // 'C'
          static char buffer[4];

          param_1 = _getFirstInt(inStrg);
          if (param_1 > 0) {
            if (irtx.changeToChannel(itoa(param_1, buffer, 10))) {
                _echoCommand(7, param_1);
            }
          }
          break; 

        case 8: // 'M'
          if (irtx.muteOnOff()) Serial.println(commands[8]);
          break; 

        case 9: // 'CC'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxCCRpts) {
            if (irtx.closedCaptioningOnOff(param_1)) {
                _echoCommand(9, param_1);
            }
          }
          break; 

        case 10: // 'S'
          if (irtx.source()) Serial.println(commands[10]);
          break; 

        case 11: // 'UARW'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxArwRpts) {
            if (irtx.upArrow(param_1)) {
                _echoCommand(11, param_1);
            }
          }
          break; 

        case 12: // 'DARW'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxArwRpts) {
            if (irtx.downArrow(param_1)) {
                _echoCommand(12, param_1);
            }
          }
          break; 

        case 13: // 'LARW'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxArwRpts) {
            if (irtx.leftArrow(param_1)) {
                _echoCommand(13, param_1);
            }
          }
          break; 

        case 14: // 'RARW'
          param_1 = _getFirstInt(inStrg);
          if (param_1 >= 0 && param_1 < maxArwRpts) {
            if (irtx.rightArrow(param_1)) {
                _echoCommand(14, param_1);
            }
          }
          break; 

        case 15: // 'OK'
          if (irtx.okayEnter()) Serial.println(commands[15]);
          break; 

        case 16: // 'RBTN'
          if (irtx.redButton()) Serial.println(commands[16]);
          break; 

        case 17: // 'GBTN'
          if (irtx.greenButton()) Serial.println(commands[17]);
          break; 

        case 18: // 'YBTN'
          if (irtx.yellowButton()) Serial.println(commands[18]);
          break; 

        case 19: // 'BBTN'
          if (irtx.blueButton()) Serial.println(commands[19]);
          break; 

        case 20: // 'MODE'
          param_1 = _getFirstInt(inStrg);
          if (irtx.setMode(param_1)) {
              _echoCommand(20, param_1);
          }
          break; 

        case 21: // 'MODE?'
          irtx.getMode();
          break; 

        case 22: // 'MODES?'
          irtx.getEEModes();
          break; 

        case 23: // 'JSON?'
          irtx.getModeJSON();
          break; 

        case 24: // 'EE?'
          eeprom.dump();
          break; 

        case 25: // 'CLR'
          _printPrgMemStr(wait_msg);
          eeprom.clear();
          _printPrgMemStr(ee_clear_msg);
          break; 

        case 26: // 'FILL'
          _printPrgMemStr(wait_msg);
          eeprom.fill();
          _printPrgMemStr(ee_fill_msg);
          break; 

        case 27: // '??'
          _printPrgMemStr(star_msg);
          _printPrgMemStr(warning);
          _printPrgMemStr(star_msg);
          _printPrgMemStr(adv_msg);
          _printPrgMemStr(star_msg);
          break; 

        case 28: // 'B'
          if (_getEepromHexAddr(inStrg) >= 0) {

                String str = _getSecondParameter(inStrg);
                if (_hasHexPrefix(str)) {
                    str = str.substring(2);
                    if (str.length() != 2) return;

                    for (int i = 0 ; i < str.length() ; i++) {
                        if (!isHexadecimalDigit(str[i])) return;
                    }

                    eeprom.write_byte(_getEepromHexAddr(inStrg), (byte) _hexToInt(str)); 

                    Serial.print(commands[28]); Serial.print(" ");
                    Serial.print(_getFirstParameter(inStrg)); Serial.print(" ");
                    _outputHexBytes(inStrg, 1);
                }
          } 
          break; 

        case 29: // 'B?'
          if (_getEepromHexAddr(inStrg) >= 0) {

                Serial.print(commands[28]); Serial.print(" ");
                Serial.print(_getFirstParameter(inStrg)); Serial.print(" ");
                _outputHexBytes(inStrg, 1);
          } 
          break; 

        case 30: // 'FLASH?'
          irtx.getFlashModeList();
          break; 

        case 31: // 'RESET'
          _printPrgMemStr(wait_msg);
          irtx.resetModes();
          Serial.println(commands[31]);
          break; 

        case 32: // 'RM'
          param_1 = _getFirstInt(inStrg);
          param_2 = _getSecondInt(inStrg);
          if (param_1 >= 0 &&\
              param_2 >= 0 &&\
              param_1 < irtx.modeCount() &&  \
              param_2 < irtx.defaultModeCount()) {

              if (irtx.resetModeToDefault(param_1, param_2)) {
                Serial.print(commands[32]); Serial.print(" ");
                Serial.print(param_1); Serial.print(" ");
                Serial.println(param_2);
              }
          }
          break; 

        case 33: // 'DW'
          if (_getEepromHexAddr(inStrg) >= 0) {

                String str = _getSecondParameter(inStrg);
                if (_hasHexPrefix(str)) {
                    str = str.substring(2);
                    if (str.length() != 8) return;

                    for (int i = 0 ; i < str.length() ; i++) {
                        if (!isHexadecimalDigit(str[i])) return;
                    }

                    int index = 3;
                    for (int i = 0 ; i < str.length() ; i+=2) {
                        eeprom.write_byte(_getEepromHexAddr(inStrg)+index, (byte) _hexToInt(str.substring(i, i+2))); 
                        index--;
                    }

                    Serial.print(commands[33]); Serial.print(" ");
                    Serial.print(_getFirstParameter(inStrg)); Serial.print(" ");
                    _outputHexBytes(inStrg, 4);
                }
          } 
          break; 

        case 34: // 'DW?'
          if (_getEepromHexAddr(inStrg) >= 0) {
                
                Serial.print(commands[33]); Serial.print(" ");
                Serial.print(_getFirstParameter(inStrg)); Serial.print(" ");
                _outputHexBytes(inStrg, 4);
          } 
          break; 

        case 35: // 'FREE?'
          Serial.print(commands[35]); Serial.print(" "); Serial.println(irtx.freeRAM());
          break; 

        default:
          // Ignore invalid commands
          return;
    }
}
