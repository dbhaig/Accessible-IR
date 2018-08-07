/* protocol.cpp
 *
 *    infrared protocol Class
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */

#include "eeprom.h"
#include "protocol.h"

extern EeProm eeprom;

#define P(name) const byte PROGMEM name[]  //declare a program memory string                                                                      


void Protocol::_printP(const byte PROGMEM *str) {
    // From Arduino Cookbook with updates
    char c;

    while (( c = pgm_read_byte(str++))) Serial.write(c);
    Serial.write('\r');
    Serial.write('\n');
}

void Protocol::_printEE(byte* str) {
    char c;

    while (( c = eeprom.read_byte(str++))) Serial.write(c);

}

void Protocol::_print_flash_tx_mode(int num) {
    Serial.print(F("# Flash ")); Serial.print(num); Serial.print(F(": "));
    _printP(flash_tx_modes[num]->description);
}

void Protocol::_print_eeprom_tx_mode(int num) {
    TxMode* tx_mode = (long) calculate_eeprom_address(num);
    //Serial.println((int)tx_mode, HEX);
    Serial.print(F("# ")); Serial.print(num); Serial.print(F(": "));
    _printEE(tx_mode->description);
    Serial.write('\r');
    Serial.write('\n');
}


void Protocol::_print_mode_info_from_progmem(TxMode *p) {
        //Serial.print("Size of structure:");
        //Serial.println(sizeof(*p));
        Serial.println("{");
        Serial.print(F("  \"description\" : { \"bytes\" : 30, \"string\" : \""));
        _printEE(p->description);  //Required because structure is stored in EEPROM
        Serial.println("\" },");
        Serial.print(F("  \"protocol\" : { \"bytes\" : 1, \"int\" : "));
        Serial.print(irlib2_protocol(),HEX);Serial.println(" },");
        Serial.print(F("  \"kHz\" : { \"bytes\" : 1, \"int\" : "));
        Serial.print(khz(),DEC);Serial.println(" },");
        Serial.print(F("  \"bits\" : { \"bytes\" : 1, \"int\" : "));
        Serial.print(bits(),DEC);Serial.println(" },");
        Serial.print(F("  \"powerOnOff\" : \"0x"));
        Serial.print(power_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"volumeUp\" : \"0x"));
        Serial.print(volume_up_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"volumeDown\" : \"0x"));
        Serial.print(volume_down_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"channelUp\" : \"0x"));
        Serial.print(channel_up_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"channelDown\" : \"0x"));
        Serial.print(channel_down_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"digitOne\" : \"0x"));
        Serial.print(digit_code(1),HEX);Serial.println("\",");
        Serial.print(F("  \"digitTwo\" : \"0x"));
        Serial.print(digit_code(2),HEX);Serial.println("\",");
        Serial.print(F("  \"digitThree\" : \"0x"));
        Serial.print(digit_code(3),HEX);Serial.println("\",");
        Serial.print(F("  \"digitFour\" : \"0x"));
        Serial.print(digit_code(4),HEX);Serial.println("\",");
        Serial.print(F("  \"digitFive\" : \"0x"));
        Serial.print(digit_code(5),HEX);Serial.println("\",");
        Serial.print(F("  \"digitSix\" : \"0x"));
        Serial.print(digit_code(6),HEX);Serial.println("\",");
        Serial.print(F("  \"digitSeven\" : \"0x"));
        Serial.print(digit_code(7),HEX);Serial.println("\",");
        Serial.print(F("  \"digitEight\" : \"0x"));
        Serial.print(digit_code(8),HEX);Serial.println("\",");
        Serial.print(F("  \"digitNine\" : \"0x"));
        Serial.print(digit_code(9),HEX);Serial.println("\",");
        Serial.print(F("  \"digitZero\" : \"0x"));
        Serial.print(digit_code(0),HEX);Serial.println("\",");
        Serial.print(F("  \"muteOnOff\" : \"0x"));
        Serial.print(mute_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"closedCaption\" : \"0x"));
        Serial.print(closed_caption_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"source\" : \"0x"));
        Serial.print(source_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"upArrow\" : \"0x"));
        Serial.print(up_arrow_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"downArrow\" : \"0x"));
        Serial.print(down_arrow_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"leftArrow\" : \"0x"));
        Serial.print(left_arrow_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"rightArrow\" : \"0x"));
        Serial.print(right_arrow_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"okayEnter\" : \"0x"));
        Serial.print(okay_enter_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"redButton\" : \"0x"));
        Serial.print(red_button_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"greenButton\" : \"0x"));
        Serial.print(green_button_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"yellowButton\" : \"0x"));
        Serial.print(yellow_button_code(),HEX);Serial.println("\",");
        Serial.print(F("  \"blueButton\" : \"0x"));
        Serial.print(blue_button_code(),HEX);Serial.println("\"");
        Serial.println("}");
}

void Protocol::_write_protocol_to_eeprom(int ee_addr, const byte PROGMEM *protocol) {

    int i = sizeof(struct TxMode);
    char c;

    while ( i > 0 ) {
        c = pgm_read_byte(protocol++);
        eeprom.write_byte(ee_addr, c);
        ee_addr++;
        i--;
    }
}

void Protocol::_write_blank_protocol_to_eeprom(int ee_addr) {

    int i = sizeof(struct TxMode);
    char c = 0;

    while ( i > 0 ) {
        eeprom.write_byte(ee_addr, c);
        ee_addr++;
        i--;
    }
}

Protocol::Protocol() {
    flash_tx_modes[0] = &mode_0;
    flash_tx_modes[1] = &mode_1;
    //flash_tx_modes[2] = &mode_2;
    //flash_tx_modes[3] = &mode_3;
    //flash_tx_modes[4] = &mode_x;
    //flash_tx_modes[5] = &mode_x;
    //flash_tx_modes[6] = &mode_x;

    _flash_mode_count = sizeof(flash_tx_modes)/sizeof(*flash_tx_modes);
    _ee_mode_count = NUMBER_OF_EE_MODES;

    for (int i=0; i < _ee_mode_count; i++) {
        ee_tx_modes[i] = PROTOCOLS_START + i*sizeof(struct TxMode);
    }

    if (eeprom.read_byte(MODE_COUNT) != _ee_mode_count) {
        reset_ee_modes();
    }
    
    _current_mode = eeprom.read_byte(CURRENT_MODE);

    if (_current_mode < 0 || _current_mode >= _ee_mode_count) {
        eeprom.write_byte(CURRENT_MODE, 0x00);
        _current_mode = 1;
    }
}

int  Protocol::calculate_eeprom_address(int mode_number) {
    if ( mode_number < 0 ) return  PROTOCOLS_START;

    if ( mode_number >= 0 && mode_number < _ee_mode_count ) 
        return  PROTOCOLS_START + mode_number * sizeof(struct TxMode);
    
    if ( mode_number >= _ee_mode_count) 
        return  PROTOCOLS_START + (_ee_mode_count -1) * sizeof(struct TxMode);

}  

bool Protocol::reset_ee_mode(int mode, int flashMode) {
    int ee_address;
    const byte PROGMEM *protocol;

    ee_address = calculate_eeprom_address(mode);

    if ( mode >= 0 && mode < _ee_mode_count && \
         flashMode >=0 && flashMode < getFlashModeCount()) {
        protocol = (const unsigned char*) flash_tx_modes[flashMode];
        _write_protocol_to_eeprom(ee_address, protocol);
        return true;
    } else {
        if ( mode >= 0 && mode < _ee_mode_count ) {
            _write_blank_protocol_to_eeprom(ee_address);
            return true;
        } else {
            return false;
        }
    }
}

void Protocol::reset_ee_modes() {
    int ee_address;
    const byte PROGMEM *protocol;

    for (int i = 0; i < _ee_mode_count; i++) {
        reset_ee_mode(i,i);
    }

    eeprom.write_byte(MODE_COUNT, _ee_mode_count);
}

bool Protocol::change_mode_to(int i) {

    if (i >= 0 && i < _ee_mode_count) {
        eeprom.write_byte(CURRENT_MODE, i);
        _current_mode = eeprom.read_byte(CURRENT_MODE);
        return true;
    }

    return false;
}

int  Protocol::getModeCount() {
    return _ee_mode_count;
}

int  Protocol::getFlashModeCount() {
    return sizeof(flash_tx_modes)/sizeof(*flash_tx_modes);
}

byte Protocol::irlib2_protocol() {
    return eeprom.read_byte(&ee_tx_modes[_current_mode]->protocol);
}

byte Protocol::khz() {
    return eeprom.read_byte(&ee_tx_modes[_current_mode]->khz);
}

byte Protocol::bits() {
    return eeprom.read_byte(&ee_tx_modes[_current_mode]->bits);
}


unsigned long Protocol::power_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->powerOnOff);
}


unsigned long Protocol::volume_up_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->volumeUp);
}


unsigned long Protocol::volume_down_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->volumeDown);
}


unsigned long Protocol::channel_up_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->channelUp);
}


unsigned long Protocol::channel_down_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->channelDown);
}


unsigned long Protocol::digit_code(int digit) {
    switch (digit) {
        case 0:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitZero);
            break;
            
        case 1:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitOne);
            break;
            
        case 2:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitTwo);
            break;
            
        case 3:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitThree);
            break;
            
        case 4:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitFour);
            break;
            
        case 5:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitFive);
            break;
            
        case 6:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitSix);
            break;
            
        case 7:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitSeven);
            break;
            
        case 8:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitEight);
            break;
            
        case 9:
            return eeprom.read_dword(&ee_tx_modes[_current_mode]->digitNine);
            break;
            
        default:
            return 0;
            break;
    }
}


unsigned long Protocol::mute_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->muteOnOff);
}


unsigned long Protocol::closed_caption_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->closedCaption);
}


unsigned long Protocol::source_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->source);
}


unsigned long Protocol::up_arrow_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->upArrow);
}


unsigned long Protocol::down_arrow_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->downArrow);
}


unsigned long Protocol::left_arrow_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->leftArrow);
}


unsigned long Protocol::right_arrow_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->rightArrow);
}


unsigned long Protocol::okay_enter_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->okayEnter);
}


unsigned long Protocol::red_button_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->redButton);
}


unsigned long Protocol::green_button_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->greenButton);
}


unsigned long Protocol::yellow_button_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->yellowButton);
}


unsigned long Protocol::blue_button_code() {
    return eeprom.read_dword(&ee_tx_modes[_current_mode]->blueButton);
}


void Protocol::print_current_mode() {
    Serial.print(F("MODE ")); Serial.println(_current_mode);
}


void Protocol::print_eeprom_tx_modes() {

    for (int i = 0; i < _ee_mode_count; i++) _print_eeprom_tx_mode(i);
}


void Protocol::print_flash_tx_modes() {

    //Serial.println("# Transmission Modes stored in FLASH memory:");
    for (int i = 0; i < _flash_mode_count; i++) _print_flash_tx_mode(i);
}


void Protocol::print_mode_details() {
    _print_mode_info_from_progmem(ee_tx_modes[_current_mode]);
}
