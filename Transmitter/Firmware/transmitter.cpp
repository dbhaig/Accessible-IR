/* transmitter.cpp
 *
 *    Transmitter class to generate infrared signals
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */

#include <Arduino.h>
#include "free.h"
#include "protocol.h"
#include "transmitter.h"

Protocol protocol;

IRsend led; 

Transmitter::Transmitter() {
}

void Transmitter::_transmit(byte irlib2_protocol, unsigned long code, int repeats) {
        //Serial.print("Protocol:");Serial.println(irlib2_protocol);
        //Serial.print("Code:");Serial.println(code,HEX);
        //Serial.print("Repeat "); Serial.print(repeats); Serial.println(" times.");
        led.send(irlib2_protocol, code, (uint8_t)protocol.bits(), (uint8_t) protocol.khz());

        while (repeats > 0) {
            delay(ms_delay);
            led.send(irlib2_protocol, code, (uint8_t)protocol.bits(), (uint8_t) protocol.khz());
            repeats--;
        } 
}

int  Transmitter::modeCount() {
    return protocol.getModeCount();
}    

int  Transmitter::defaultModeCount() {
    return protocol.getFlashModeCount();
}    

bool Transmitter::powerOnOff() {
    if (protocol.power_code() != 0) {
        //Serial.println("Send Power On/Off Signal");
        _transmit(protocol.irlib2_protocol(), protocol.power_code(), 0);
        return true;
    }

    return false;
}

bool Transmitter::volumeUp(int count) {
    if (protocol.volume_up_code() != 0) {
        //Serial.println("Send Volume Up Signal");
        _transmit(protocol.irlib2_protocol(), protocol.volume_up_code(), count);
        return true;
    }

    return false;
}

bool Transmitter::volumeDown(int count) {
    if (protocol.volume_down_code() != 0) {
        //Serial.println("Send Volume Down Signal");
        _transmit(protocol.irlib2_protocol(), protocol.volume_down_code(), count);
        return true;
    }

    return false;
}

bool Transmitter::channelUp(int count) {
    if (protocol.channel_up_code() != 0) {
        //Serial.println("Send Channel Up Signal");
        _transmit(protocol.irlib2_protocol(), protocol.channel_up_code(), count);
        return true;
    }

    return false;
}

bool Transmitter::channelDown(int count) {
    if (protocol.channel_down_code() != 0) {
        //Serial.println("Send Channel Down Signal");
        _transmit(protocol.irlib2_protocol(), protocol.channel_down_code(), count);
        return true;
    }

    return false;
}

bool Transmitter::changeToChannel(String num) {
    int i;

    //Serial.print("Change Channel to '"); Serial.print(num); Serial.println("'.");
    for (i=0; i<num.length(); i++) {
        switch (num[i]) {
            case '1':
                //Serial.println("Send '1'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(1), 0);
                break;

            case '2':
                //Serial.println("Send '2'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(2), 0);
                break;

            case '3':
                //Serial.println("Send '3'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(3), 0);
                break;

            case '4':
                //Serial.println("Send '4'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(4), 0);
                break;

            case '5':
                //Serial.println("Send '5'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(5), 0);
                break;

            case '6':
                //Serial.println("Send '6'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(6), 0);
                break;

            case '7':
                //Serial.println("Send '7'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(7), 0);
                break;

            case '8':
                //Serial.println("Send '8'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(8), 0);
                break;

            case '9':
                //Serial.println("Send '9'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(9), 0);
                break;

            case '0':
                //Serial.println("Send '0'");
                _transmit(protocol.irlib2_protocol(), protocol.digit_code(0), 0);
                break;

            default:
                return false;
                break;
        }
        delay(ms_delay);
    }
    return true;
}

bool Transmitter::muteOnOff() {
    if (protocol.mute_code() != 0) {
        //Serial.println("Send Mute On/Off Signal");
        _transmit(protocol.irlib2_protocol(), protocol.mute_code(), 0);
        return true;
    }

    return false;
}


bool Transmitter::closedCaptioningOnOff(int count) {
    if (protocol.closed_caption_code() != 0) {
        //Serial.println("Send Closed Captioning On/Off Signal");
        _transmit(protocol.irlib2_protocol(), protocol.closed_caption_code(), count);
        return true;
    }

    return false;
}


bool Transmitter::source() {
    if (protocol.source_code() != 0) {
        //Serial.println("Send Source Signal");
        _transmit(protocol.irlib2_protocol(), protocol.source_code(), 0);
        return true;
    }

    return false;
}


bool Transmitter::upArrow(int count) {
    if (protocol.up_arrow_code() != 0) {
        //Serial.println("Send Up Arrow Signal");
        _transmit(protocol.irlib2_protocol(), protocol.up_arrow_code(), count);
        return true;
    }

    return false;
}


bool Transmitter::downArrow(int count) {
    if (protocol.down_arrow_code() != 0) {
        //Serial.println("Send Down Arrow Signal");
        _transmit(protocol.irlib2_protocol(), protocol.down_arrow_code(), count);
        return true;
    }

    return false;
}


bool Transmitter::leftArrow(int count) {
    if (protocol.left_arrow_code() != 0) {
        //Serial.println("Send Left Arrow Signal");
        _transmit(protocol.irlib2_protocol(), protocol.left_arrow_code(), count);
        return true;
    }

    return false;
}


bool Transmitter::rightArrow(int count) {
    if (protocol.right_arrow_code() != 0) {
        //Serial.println("Send Right Arrow Signal");
        _transmit(protocol.irlib2_protocol(), protocol.right_arrow_code(), count);
        return true;
    }

    return false;
}


bool Transmitter::okayEnter() {
    if (protocol.okay_enter_code() != 0) {
        //Serial.println("Send Okay/Enter Signal");
        _transmit(protocol.irlib2_protocol(), protocol.okay_enter_code(), 0);
        return true;
    }

    return false;
}


bool Transmitter::redButton() {
    if (protocol.red_button_code() != 0) {
        //Serial.println("Send Red Button Signal");
        _transmit(protocol.irlib2_protocol(), protocol.red_button_code(), 0);
        return true;
    }

    return false;
}


bool Transmitter::greenButton() {
    if (protocol.green_button_code() != 0) {
        //Serial.println("Send Green Button Signal");
        _transmit(protocol.irlib2_protocol(), protocol.green_button_code(), 0);
        return true;
    }

    return false;
}


bool Transmitter::yellowButton() {
    if (protocol.yellow_button_code() != 0) {
        //Serial.println("Send Yellow Button Signal");
        _transmit(protocol.irlib2_protocol(), protocol.yellow_button_code(), 0);
        return true;
    }

    return false;
}


bool Transmitter::blueButton() {
    if (protocol.blue_button_code() != 0) {
        //Serial.println("Send Blue Button Signal");
        _transmit(protocol.irlib2_protocol(), protocol.blue_button_code(), 0);
        return true;
    }

    return false;
}


bool Transmitter::setMode(int mode) {
    return protocol.change_mode_to(mode);
}

void Transmitter::getMode() {
    protocol.print_current_mode();
}

void Transmitter::getFlashModeList() {
    protocol.print_flash_tx_modes();
}

void Transmitter::getEEModes() {
    protocol.print_eeprom_tx_modes();
}

void Transmitter::getModeJSON() {
    protocol.print_mode_details();
}

bool Transmitter::resetModeToDefault(int mode, int defaultMode) {
    return protocol.reset_ee_mode(mode, defaultMode);
}

void Transmitter::resetModes() {
    protocol.reset_ee_modes();
}

int Transmitter::freeRAM() {
    return memoryFree();
}
