/* protocol.h
 *
 *    infrared protocol information
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details)·
 *
 */
 
#ifndef PROTOCOL_h
#define PROTOCOL_h

#include "eeprom.h"
#include "protocols.h"
#include <IRLibSendBase.h>
#include <IRLib_P01_NEC.h>   // Lowest numbers must be first
#include <IRLib_P02_Sony.h>
#include <IRLib_P03_RC5.h>
#include <IRLib_P04_RC6.h>
#include <IRLib_P05_Panasonic_Old.h>
#include <IRLib_P06_JVC.h>
#include <IRLib_P07_NECx.h>
#include <IRLib_P08_Samsung36.h>
#include <IRLib_P09_GICable.h>
#include <IRLib_P10_DirecTV.h>
#include <IRLibCombo.h>     // Combine them into "IRsend"  
#include <IRLibProtocols.h>

#define NUMBER_OF_EE_MODES 7      // Number of mode structures that will fit in EEPROM  
#define NUMBER_OF_FLASH_MODES 2      // Number of mode structures that will fit in PROGMEM  
#define CURRENT_MODE    EE_LAST_ADDR - 2
#define MODE_COUNT EE_LAST_ADDR - 1  // Location in EEPROM that holds number of Modes , (should equal EE_MODES)
#define PROTOCOLS_START 0x00   


class Protocol
{
    private:
        TxMode* flash_tx_modes[NUMBER_OF_FLASH_MODES];
        TxMode* ee_tx_modes[NUMBER_OF_EE_MODES];
        int _flash_mode_count;
        int _ee_mode_count;
        int _current_mode;

        void _printP(const byte PROGMEM *str);
        void _printEE(byte* str); 
        void _print_flash_tx_mode(int num); 
        void _print_eeprom_tx_mode(int num); 
        void _print_mode_info_from_progmem(TxMode *p); 
        void _write_protocol_to_eeprom(int ee_addr, const byte PROGMEM *protocol);
        void _write_blank_protocol_to_eeprom(int ee_addr); 

    public:
        Protocol();
        int  calculate_eeprom_address(int mode_number);
        bool reset_ee_mode(int mode, int defaultMode); 
        void reset_ee_modes();
        bool load_protocol_from_progmem(int Protocol_number, int eeprom_location);
        bool change_mode_to(int i);
        int  getModeCount();
        int  getFlashModeCount();
        byte irlib2_protocol();
        byte khz();
        byte bits();
        unsigned long power_code();
        unsigned long volume_up_code();
        unsigned long volume_down_code();
        unsigned long channel_up_code();
        unsigned long channel_down_code();
        unsigned long digit_code(int digit);
        unsigned long mute_code();
        unsigned long closed_caption_code();
        unsigned long source_code();
        unsigned long up_arrow_code();
        unsigned long down_arrow_code();
        unsigned long left_arrow_code();
        unsigned long right_arrow_code();
        unsigned long okay_enter_code();
        unsigned long red_button_code();
        unsigned long green_button_code();
        unsigned long yellow_button_code();
        unsigned long blue_button_code();
        void print_current_mode();
        void print_tx_modes(); 
        void print_eeprom_tx_modes(); 
        void print_flash_tx_modes(); 
        void print_mode_details();
};
#endif
