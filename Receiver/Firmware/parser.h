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

#define P(name) const byte PROGMEM name[]  //declare a program memory string

P(idn_msg) = "*IDN Accessible IR Rx module - V 1.0\r\n";

P(help_msg) =  "# ?              - This help menu.\r\n"
               "# *IDN?          - ID string.\r\n"
               "# FREE          - ID string.\r\n";


P(star_msg) =  "# ***********************\r\n";

const String commands [] = {"?",
                            "*IDN?",
                            "FREE?"
                            };

class Parser
{
    private:
        int _cmdCnt = 2;  //Number of commands in commands[]
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
        int _getSecondHex(String str);
        void _echoCommand(int command_num, int param);
//        void _outputHexBytes(String inStrg, int count);

    public:
        Parser();
        void command(String inStrg);
        void sendIDN();
};
#endif
