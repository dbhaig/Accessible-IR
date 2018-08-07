# Accessible IR Receiver Module

This module is designed to analyze infrared signals from remote controls used to operate consumer electronic
devices. 

## Hardware

Module I2C interface is a female TRRS (Tip-Ring1-Ring2-Shield) connector, wired as follow:
 
    * Tip    - 5 Volts
    * Ring1  - SCL
    * Ring2  - SDA
    * Shield - Ground

## Commands

This module communicates via I2C, with an address of TBD, and understands the following commands:

   ##### Basic Commands
    * '?'   return module version information over I2C

   ##### Advanced Commands
    * '+'   return module information (full version) over I2C

    **commands for programming module TBD**

Valid command delimiters are 'carriage return', 'linefeed' or 'semi-colon'

### Acknowledgements

The firmware for this module uses the IRLIb2 libraries written by Chris Young: https://github.com/cyborg5/IRLib2 

Thank you Chris!
