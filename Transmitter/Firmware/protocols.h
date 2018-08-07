/* protocols.h
 *
 *    infrared protocol information
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */
 
#ifndef PROTOCOLS_h
#define PROTOCOLS_h
#include <IRLibProtocols.h>

struct TxMode {
    char description[30];
    byte  protocol;
    byte  khz;
    byte  bits;
    unsigned long powerOnOff;

    unsigned long volumeUp;
    unsigned long volumeDown;

    unsigned long channelUp;
    unsigned long channelDown;

    unsigned long digitOne;
    unsigned long digitTwo;
    unsigned long digitThree;
    unsigned long digitFour;
    unsigned long digitFive;
    unsigned long digitSix;
    unsigned long digitSeven;
    unsigned long digitEight;
    unsigned long digitNine;
    unsigned long digitZero;


    unsigned long muteOnOff;
    unsigned long closedCaption;
    unsigned long source;

    unsigned long upArrow;
    unsigned long downArrow;
    unsigned long leftArrow;
    unsigned long rightArrow;
    unsigned long okayEnter;

    unsigned long redButton;
    unsigned long greenButton;
    unsigned long yellowButton;
    unsigned long blueButton;
};


const PROGMEM TxMode mode_0 = { "Samsung TV\0", // Dev:7 Sub:7
                                NECX,        // IRLib protocol identifier
                                38,          // carrier frequency
                                32,          // number of bits
                                0xE0E040BF,  // Power On/Off
                                0xE0E0E01F,  // Volume Up
                                0xE0E0D02F,  // Volume Down
                                0xE0E048B7,  // Channel Up
                                0xE0E008F7,  // Channel Down
                                0xE0E020DF,  // One
                                0xE0E0A05F,  // Two
                                0xE0E0609F,  // Three
                                0xE0E010EF,  // Four
                                0xE0E0906F,  // Five
                                0xE0E050AF,  // Six
                                0xE0E030CF,  // Seven
                                0xE0E0B04F,  // Eight
                                0xE0E0708F,  // Nine
                                0xE0E08877,  // Zero
                                0xE0E0F00F,  // Mute On/Off
                                0xE0E0A45B,  // Closed Caption On/Off
                                0xE0E0807F,  // Source
                                0xE0E006F9,  // Up Arrow
                                0xE0E08679,  // Down Arrow
                                0xE0E0A659,  // Left Arrow
                                0xE0E046B9,  // Right Arrow
                                0xE0E016E9,  // OK/Enter
                                0xE0E036C9,  // Red Button
                                0xE0E028D7,  // Green Button
                                0xE0E0A857,  // Yellow Button
                                0xE0E06897   // Blue Button
                              };


const PROGMEM TxMode mode_1 = { "LG TV\0",
                                NEC,         // IRLib protocol identifier
                                38,          // carrier frequency
                                32,          // number of bits
                                0x20DF10EF,  // Power On/Off
                                0x20DF40BF,  // Volume Up
                                0x20DFC03F,  // Volume Down
                                0x20DF00FF,  // Channel Up
                                0x20DF807F,  // Channel Down
                                0x20DF8877,  // One
                                0x20DF48B7,  // Two
                                0x20DFC837,  // Three
                                0x20DF28D7,  // Four
                                0x20DFA857,  // Five
                                0x20DF6897,  // Six
                                0x20DFE817,  // Seven
                                0x20DF18E7,  // Eight
                                0x20DF9867,  // Nine
                                0x20DF08F7,  // Zero
                                0x20DF906F,  // Mute On/Off
                                0x20DF9C63,  // Closed Caption On/Off
                                0x20DFD02F,  // Source
                                0x20DF02FD,  // Up Arrow
                                0x20DF827D,  // Down Arrow
                                0x20DF609F,  // Left Arrow
                                0x20DFE01F,  // Right Arrow
                                0x20DF22DD,  // OK/Enter
                                0x20DF4EB1,  // Red Button
                                0x20DF8E71,  // Green Button
                                0x20DFC639,  // Yellow Button
                                0x20DF8679   // Blue Button
                              };

const PROGMEM TxMode mode_2 = { "4642HD Cable Box\0",
                                PANASONIC_OLD, // IRLib protocol identifier
                                57,          // carrier frequency
                                22,          // number of bits
                                0x37C107,    // Power On/Off
                                0x000000,    // Volume Up
                                0x000000,    // Volume Down
                                0x377111,    // Channel Up
                                0x36F121,    // Channel Down
                                0x36113D,    // One
                                0x37111D,    // Two
                                0x36912D,    // Three
                                0x37910D,    // Four
                                0x365135,    // Five
                                0x375115,    // Six
                                0x36D125,    // Seven
                                0x37D105,    // Eight
                                0x363139,    // Nine
                                0x373119,    // Zero
                                0x000000,    // Mute On/Off
                                0x000000,    // Closed Caption On/Off
                                0x376113,    // Source
                                0x36812F,    // Up Arrow
                                0x37A10B,    // Down Arrow
                                0x37810F,    // Left Arrow
                                0x364137,    // Right Arrow
                                0x366133,    // OK/Enter
                                0x37191C,    // Red Button
                                0xF7E10,     // Green Button
                                0x37E902,    // Yellow Button
                                0x36193C     // Blue Button
                              };

const PROGMEM TxMode mode_3 = { "Windows Media Center\0",
                                RC6,         // IRLib protocol identifier
                                36,          // carrier frequency
                                32,          // number of bits
                                0x800F040C,  // Power On/Off
                                0x800F8410,  // Volume Up
                                0x800F8411,  // Volume Down
                                0x800F0412,  // Channel Up
                                0x800F8413,  // Channel Down
                                0x800F0401,  // One
                                0x800F0402,  // Two
                                0x800F0403,  // Three
                                0x800F0404,  // Four
                                0x800F0405,  // Five
                                0x800F0406,  // Six
                                0x800F0407,  // Seven
                                0x800F0408,  // Eight
                                0x800F0409,  // Nine
                                0x800F0400,  // Zero
                                0x800F840E,  // Mute On/Off
                                0x800F040F,  // Closed Caption On/Off
                                0x00000000,  // Source
                                0x800F041E,  // Up Arrow
                                0x800F041F,  // Down Arrow
                                0x800F8420,  // Left Arrow
                                0x800F0421,  // Right Arrow
                                0x800F8422,  // OK/Enter
                                0x800F841D,  // Red Button (Asterix)
                                0x800F040D,  // Green (Microsoft) Button
                                0x00000000,  // Yellow Button
                                0x00000000   // Blue Button
                              };

//const PROGMEM TxMode mode_x = { "Empty\0",
//                                0x00,        // IRLib protocol identifier
//                                0x00,        // carrier frequency
//                                0x00,        // number of bits
//                                0x00000000,  // Power On/Off
//                                0x00000000,  // Volume Up
//                                0x00000000,  // Volume Down
//                                0x00000000,  // Channel Up
//                                0x00000000,  // Channel Down
//                                0x00000000,  // One
//                                0x00000000,  // Two
//                                0x00000000,  // Three
//                                0x00000000,  // Four
//                                0x00000000,  // Five
//                                0x00000000,  // Six
//                                0x00000000,  // Seven
//                                0x00000000,  // Eight
//                                0x00000000,  // Nine
//                                0x00000000,  // Zero
//                                0x00000000,  // Mute On/Off
//                                0x00000000,  // Closed Caption On/Off
//                                0x00000000,  // Source
//                                0x00000000,  // Up Arrow
//                                0x00000000,  // Down Arrow
//                                0x00000000,  // Left Arrow
//                                0x00000000,  // Right Arrow
//                                0x00000000,  // OK/Enter
//                                0x00000000,  // Red Button (Asterix)
//                                0x00000000,  // Green (Microsoft) Button
//                                0x00000000,  // Yellow Button
//                                0x00000000   // Blue Button
//                              };
#endif
