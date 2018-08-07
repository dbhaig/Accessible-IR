/* eeprom.cpp
 *
 *    EEPROM class to store infrared code parameters
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *   GNU GPLv3 (See LICENSE for details)
 *
 */
 
#include "eeprom.h"
 
EeProm::EeProm() {
    if (read_byte(EE_LAST_ADDR) != EE_MARKER_BYTE) {
        clear();

        write_byte(EE_LAST_ADDR, EE_MARKER_BYTE);
    }
}


boolean EeProm::_addr_ok(int addr) {
    return ((addr >= 0) && (addr < EEPROM.length()));
}

  
boolean EeProm::_write_bytes(int startAddr, const byte* array, int numBytes) {
    int i;
 
    if (!_addr_ok(startAddr) || !_addr_ok(startAddr + numBytes)) {
        return false;
    }
 
    for (i = 0; i < numBytes; i++) {
        EEPROM.write(startAddr + i, array[i]);
    }
 
    return true; //success
}


bool EeProm::_read_string(int addr, char* buffer, int bufSize) {
    byte ch;
    int bytesRead = 0;
 
    if (!_addr_ok(addr)) return false;
 
    if (bufSize == 0) return false;
 
    if (bufSize == 1) {
        buffer[0] = 0;
        return true;
    }
 
    do {
        ch = EEPROM.read(addr + bytesRead);
        buffer[bytesRead] = ch;
        bytesRead++;
 
    } while ((ch != 0x00) && (bytesRead < bufSize) &&\
             ((addr + bytesRead) < EEPROM.length()));

    return true;
}
 
 
boolean EeProm::_write_string(int addr, const char* string) {
 
    int numBytes;
 
    numBytes = strlen(string) + 1; // account for Null terminator
 
    return _write_bytes(addr, (const byte*)string, numBytes);
}
                                                      

void EeProm::_print_ASCII(char * buffer) {
    for(int i = 0; i < 16; i++){
        if(i == 8) Serial.print(" ");

        if(buffer[i] > 31 and buffer[i] < 127){
            Serial.print(buffer[i]);
        }else{
            Serial.print(".");
        }
    }
    Serial.println();
}

 
void  EeProm::dump() {
    char buffer[16];
    char valuePrint[4];
    byte value;
    unsigned int address;
    uint8_t trailingSpace = 2;

    // Banner
    Serial.print(F("# Dumping ")); Serial.print(EEPROM.length());
    Serial.println(F(" bytes from EEPROM."));
    Serial.print(F("# baseAddr "));

    for(int y = 0; y < 25; y++) Serial.print("=");
    Serial.print(" ");
    for(int y = 0; y < 25; y++) Serial.print("=");
    Serial.println();

    //Data
    for(address = 0; address < EEPROM.length(); address++){
        value = EEPROM.read(address);

        if(address > 0 && address % 8 == 0) Serial.print("  ");

        if(address % 16 == 0) { // newline and address for every 16 bytes
            if(address > 0 && address % 16 == 0) _print_ASCII(buffer);

            sprintf(buffer, "# 0x%05X: ", address);
            Serial.print(buffer);

            //clear the buffer for the next data block
            memset (buffer, 32, 16);
        }

        buffer[address%16] = value;

        sprintf(valuePrint, " %02X", value);
        Serial.print(valuePrint);
    }

    if(address % 16 > 0){
        if(address % 16 < 9) trailingSpace += 2;
        trailingSpace += (16 - address % 16) * 3;
    }

    for(int i = trailingSpace; i > 0; i--) Serial.print(" ");
        
    //last line of data and a new line
    _print_ASCII(buffer);
}


void EeProm::clear() {
    // Set all bits in EEPROM to 0.
    for (int i = 0 ; i < EEPROM.length() ; i++) {
            EEPROM.write(i, 0x00);
    }
}


void EeProm::fill() {
    // Set all bits in EEPROM to 1.
    for (int i = 0 ; i < EEPROM.length() ; i++) {
            EEPROM.write(i, 0xFF);
    }
}


bool EeProm::write_byte(int addr, byte b) {
    if (!_addr_ok(addr)) return false;

    EEPROM.write(addr, b);
    
    if (EEPROM.read(addr) != b) return false;

    return true;
}    


byte EeProm::read_byte(int addr) {
    return EEPROM.read(addr);
} 


unsigned long EeProm::read_dword(int addr) {
    //Read the 4 bytes from the eeprom memory.
    long four = EEPROM.read(addr);
    long three = EEPROM.read(addr + 1);
    long two = EEPROM.read(addr + 2);
    long one = EEPROM.read(addr + 3);

    //Return the recomposed long by using bitshift.
    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) +\
           ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

bool write_dword(int addr, long value) {
    //Decomposition from a long to 4 bytes by using bitshift.
    //One = Most significant -> Four = Least significant byte
    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);
    byte two = ((value >> 16) & 0xFF);
    byte one = ((value >> 24) & 0xFF);

    //Write the 4 bytes into the eeprom memory.
    EEPROM.write(addr, four);
    if (EEPROM.read(addr) != four) return false;

    EEPROM.write(addr + 1, three);
    if (EEPROM.read(addr + 1) != three) return false;

    EEPROM.write(addr + 2, two);
    if (EEPROM.read(addr + 2) != two) return false;

    EEPROM.write(addr + 3, one);
    if (EEPROM.read(addr + 3) != one) return false;

    return true;
}

String EeProm::read_string(int addr, int length) {
    char cbuff[length+1];

    _read_string(addr, cbuff, length+1);

    String stemp(cbuff);
    return stemp;
}


bool EeProm::write_string(int addr, String input) {
    char cbuff[input.length() + 1];

    input.toCharArray(cbuff, input.length() + 1);
    return _write_string(addr, cbuff);
}
