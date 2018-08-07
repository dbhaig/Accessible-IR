/* parser.h
 *
 *     Command parser class to process command strings
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */

#ifndef PARSER_H
#define PARSER_H

#define maxArwRpts  5
#define maxCCRpts   4
#define maxChnRpts 10
#define maxVolRpts 20

#define P(name) const byte PROGMEM name[]  //declare a program memory string

P(idn_msg) = "*IDN Accessible IR Tx module - V 1.0\r\n";

P(help_msg) =  "# ?              - This help menu.\r\n"
               "# ??             - Advance help menu.\r\n"
               "# *IDN?          - ID string.\r\n"
               "# P              - Power on/off\r\n"
               "# VUP [num]      - Volume up\r\n"
               "# VDN [num]      - Volume down\r\n"
               "# CUP [num]      - Channel up\r\n"
               "# CDN [num]      - Channel down\r\n"
               "# C <num>        - Channel <num>\r\n"
               "# M              - Mute on/off\r\n"
               "# CC  [num]      - Closed captioning on/off\r\n"
               "# S              - Input Source\r\n"
               "# UARW [num]     - Up Arrow\r\n"
               "# DARW [num]     - Down Arrow\r\n"
               "# LARW [num]     - Left Arrow\r\n"
               "# RARW [num]     - Right Arrow\r\n"
               "# OK             - Okay/Enter\r\n"
               "# RBTN           - Red Button\r\n"
               "# GBTN           - Green Button\r\n"
               "# YBTN           - Yellow Button\r\n"
               "# BBTN           - Blue Button\r\n"
               "# MODE <num>     - Set Tx mode\r\n"
               "# MODE?          - Get Tx Mode\r\n"
               "# MODES?         - Available Tx modes\r\n";

P(star_msg) =  "# ***********************\r\n";

P(warning)  =  "# Advanced users only.\r\n";

P(adv_msg) =   "# JSON?            - JSON for current mode\r\n"
               "# FLASH?           - Modes stored in FLASH\r\n"
               "# RM <num1> <num2> - Overwrite EEPROM MODE <num1> with FLASH mode <num2>\r\n"
               "# RESET            - Overwrite all MODES with FLASH modes\r\n"
               "# B <hex1> <hex2>  - Write byte <hex2> to EEPROM address <hex1>\r\n"
               "# B? <hex>         - Value of byte at EEPROM address <hex>\r\n"
               "# DW <hex1> <hex2> - Write DWORD <hex2> to EEPROM address <hex1>\r\n"
               "# DW? <hex>        - Value of DWORD at EEPROM address <hex>\r\n"
               "# EE?              - Contents of EEPROM\r\n"
               "# CLR              - Write 0x00 to all EEPROM\r\n"
               "# FILL             - Write 0xFF to all EEPROM\r\n";

P(wait_msg)     = "# This takes a few seconds ...'\r\n"; 
P(ee_clear_msg) = "# EEPROM set to '0x00'\r\n"; 
P(ee_fill_msg)  = "# EEPROM set to '0xFF'\r\n"; 

const String commands [] = {"?",
                            "*IDN?",
                            "P",
                            "VUP",
                            "VDN",
                            "CUP",
                            "CDN",
                            "C",
                            "M",
                            "CC",
                            "S",
                            "UARW",
                            "DARW",
                            "LARW",
                            "RARW",
                            "OK",
                            "RBTN",
                            "GBTN",
                            "YBTN",
                            "BBTN",
                            "MODE",
                            "MODE?",
                            "MODES?",
                            "JSON?",
                            "EE?",
                            "CLR",
                            "FILL",
                            "??",
                            "B",
                            "B?",
                            "FLASH?",
                            "RESET",
                            "RM",
                            "DW",
                            "DW?",
                            "FREE?"
                            };

class Parser
{
    private:
        int _cmdCnt = 36;  //Number of commands in commands[]
        void _printPrgMemStr(const byte PROGMEM *str);
        int _getCommandIndex(String str);
        String _removeBeforeSpace(String str);
        String _removeAfterSpace(String str);
        String _getFirstParameter(String str);
        String _getSecondParameter(String str);
        bool _hasHexPrefix(String str);
        int _getFirstInt(String str);
        int _getSecondInt(String str);
        int _hexToInt(String str);
        int _getEepromHexAddr(String str);
        int _getSecondHex(String str);
        void _echoCommand(int command_num, int param);
        void _outputHexBytes(String inStrg, int count);

    public:
        Parser();
        void command(String inStrg);
        void sendIDN();
};
#endif
