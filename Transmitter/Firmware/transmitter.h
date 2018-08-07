/* transmitter.h
 *
 *    Transmitter class to generate infrared signals
 *
 *    Copyright 2018 Don Haig (time4tux at gmail dot com)
 *
 *    GNU GPLv3 (See LICENSE for details) 
 *
 */

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#define ms_delay 500

class Transmitter
{
    private:
        void _transmit(byte irlib2_protocol, unsigned long code, int repeats); 

    public:
        Transmitter();
        int  modeCount();
        int  defaultModeCount();
        bool powerOnOff();
        bool volumeUp(int count);
        bool volumeDown(int count);
        bool channelUp(int count);
        bool channelDown(int count);
        bool changeToChannel(String num);
        bool muteOnOff();
        bool closedCaptioningOnOff(int count);
        bool source();
        bool upArrow(int count);
        bool downArrow(int count);
        bool leftArrow(int count);
        bool rightArrow(int count);
        bool okayEnter();
        bool redButton();
        bool greenButton();
        bool yellowButton();
        bool blueButton();
        bool setMode(int mode);
        void getMode();
        void getFlashModeList();
        void getEEModes();
        void getModeJSON();
        bool resetModeToDefault(int mode, int defaultMode);
        void resetModes();
        int  freeRAM();
};
#endif
