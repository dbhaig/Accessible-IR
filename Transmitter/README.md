# ACCESSIBLE-IR Transmitter Module

The Accessible-IR transmitter is designed to generate infrared signals for consumer electronic
devices that are normally operated via a remote control.

## Supported Protocols

The Accessible-IR transmitter module relies on Chis Young's IRLib2 library and is currently configured to support the following protocols:

    * NEC
    * Sony
    * RC-5
    * RC-6
    * Panasonic
    * JVC
    * NECx
    * Samsung36
    * GICable
    * DirecTV

Please see https://github.com/cyborg5/IRLib2 for further information.

## Hardware

Serial interface:

     USB serial interface, operating at 115200 baud.

I2C Interface:

    Address: 5

    Connector: Female TRRS (Tip-Ring1-Ring2-Shield)
 
    * Tip    - 5 Volts
    * Ring1  - SCL
    * Ring2  - SDA
    * Shield - Ground

IR LED pin used by IRLib2:

    * Arduino UNO           Pin 3
    * Arduino Leonardo      Pin 9

## User Commands

Command characters may be received via USB serial or I2C:

    Characters are all processed in the same command buffer.
    Invalid commands are ignored.
    Valid commands are actioned and echoed back to the USB serial interface, once completed.

The module understands the following commands:

     ?           Returns this help info
     ??          Returns advance help menu.
     *IDN?       Return *IDN string
     P           Power on/off
     VUP [num]   Volume up (repeat num times, default = 0)
     VDN [num]   Volume down (repeat num times, default = 0)
     CUP [num]   Channel up (repeat num times, default = 0)
     CDN [num]   Channel down (repeat num times, default = 0)
     C <num>     Change channel to <num>
     M           Mute on/off
     CC  [num]   Closed captioning on/off (repeat num times, default = 0)
     S           Input Source
     UARW [num]  Up Arrow (repeat num times, default = 0)
     DARW [num]  Down Arrow (repeat num times, default = 0)
     LARW [num]  Left Arrow (repeat num times, default = 0)
     RARW [num]  Right Arrow (repeat num times, default = 0)
     OK          Okay/Enter
     RBTN        Red Button
     GBTN        Green Button
     YBTN        Yellow Button
     BBTN        Blue Button
     MODE <num>  Set transmission mode
     MODE?       Return mode setting
     MODES?      Available transmission modes


Valid command delimiters are 'carriage return', 'linefeed' or 'semi-colon'


## Advance User Commands
  
   These commands are for troubleshooting and configuration.

   **If used improperly, some commands below may result in loss if data or misconfiguration of the module.**

     JSON?              Mode details in JSON format
     FLASH?             Modes stored in FLASH memory
     RM <num1> <num2>   Reset MODE <num1> to FLASH mode <num2> (overwrites MODE setting)
     RESET_ALL          Reset all MODES to default modes (overwrites all MODE settings)
     B <hex1> <hex2>    Write byte <hex2> to EEPROM address <hex1>
     B? <hex>           Return value of byte at EEPROM address <hex>
     DW <hex1> <hex2>   Write DWORD <hex2> to EEPROM address <hex1>
     DW? <hex>          Return value of DWORD at EEPROM address <hex>
     EE?                List contents of EEPROM
     CLEAR              Set all EEPROM bytes to 0x00
     FILL               Set all EEPROM bytes to 0xFF

Valid command delimiters are 'carriage return', 'linefeed' or 'semi-colon'


### Acknowledgements

The firmware for this module uses the IRLIb2 library written by Chris Young: https://github.com/cyborg5/IRLib2 

Thank you Chris!


Copyright 2018 Don Haig 
