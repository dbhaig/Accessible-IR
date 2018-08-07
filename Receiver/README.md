# ACCESSIBLE-IR Receiver Module

The Accessible-IR receiver is designed to capture infrared signals used to control consumer electronic
devicesi.

## Supported Protocols

The Accessible-IR receiver module relies on Chis Young's IRLib2 library and is currently configured to support the following protocols:

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

    Address: 6

    Connector: Female TRRS (Tip-Ring1-Ring2-Shield)
 
    * Tip    - 5 Volts
    * Ring1  - SCL
    * Ring2  - SDA
    * Shield - Ground

IR detector (Vishay TSOP34156) connected to pin D2.


## User Commands

Command characters may be received via USB serial or I2C:

    Characters are all processed in the same command buffer.
    Invalid commands are ignored.
    Valid commands are actioned and echoed back to the USB serial interface, once completed.

The module understands the following commands:

     ?           Returns this help info
     ??          Returns advance help menu.
     *IDN?       Return *IDN string
     (Other commands TBD)


Valid command delimiters are 'carriage return', 'linefeed' or 'semi-colon'


## Advance User Commands
  
   These commands are for troubleshooting and configuration.

   **If used improperly, some commands below may result in loss if data or misconfiguration of the module.**

     JSON?              Mode details in JSON format
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
