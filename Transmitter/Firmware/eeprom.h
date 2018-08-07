/* eeprom.h
 *
 *    EEPROM class to store infrared code parameters
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */
#include <Arduino.h>
#include "protocols.h"
#include <EEPROM.h>

#ifndef MY_EEPROM_H
#define MY_EEPROM_H

#define EE_LAST_ADDR EEPROM.length()-1
#define EE_MARKER_BYTE  0xAA

class EeProm
{
    private:

        void _print_ASCII(char * buffer);
        bool _addr_ok(int addr);
        bool _write_bytes(int startAddr, const byte* array, int numBytes);
        bool _write_string(int addr, const char* string);
        bool _read_string(int addr, char* buffer, int bufSize);

    public:
        EeProm();
        void dump();
        void clear();
        void fill();
        bool write_byte(int addr, byte b); 
        byte read_byte(int addr); 
        unsigned long read_dword(int addr); 
        bool write_dword(int addr, long value); 
        String read_string(int addr, int length);
        bool write_string(int addr, String input);
};
#endif
