#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  Copyright 2016 Don Haig (time4tux at gmail dot com)
#  GPL License (See LICENSE.txt for details)
#
# Created: Thu 29 Mar 2018 04:16:32 PM EDT -0400
# Last Modified: Tue 07 Aug 2018 14:27:32 UTC +0000

""" Test Program

"""
from __future__ import print_function
import argparse
import logging
import json
import os
import serial
from serial.tools import list_ports

# Global Values
id_cmd = b'*IDN?;'
id_bytes = b'*IDN Accessible IR Tx module - V 1.0\r\n'
baudrate = 115200
mode_bytes = 141  # Number of bytes in a protocol record
mode_count = 7    # Capacity of Tx EEPROM
serial_port = ''
offsets = {
           "description" : 0,
           "protocol" : 30,
           "kHz" : 31,
           "bits" : 32,
           "powerOnOff" : 33,
           "volumeUp" : 37,
           "volumeDown" : 41,
           "channelUp" : 45,
           "channelDown" : 49,
           "digitOne" : 53,
           "digitTwo" : 57,
           "digitThree" : 61,
           "digitFour" : 65,
           "digitFive" : 69,
           "digitSix" : 73,
           "digitSeven" : 77,
           "digitEight" : 81,
           "digitNine" : 85,
           "digitZero" : 89,
           "muteOnOff" : 93,
           "closedCaption" : 97,
           "source" : 101,
           "upArrow" : 105,
           "downArrow" : 109,
           "leftArrow" : 113,
           "rightArrow" : 117,
           "okayEnter" : 121,
           "redButton" : 125,
           "greenButton" : 129,
           "yellowButton" : 133,
           "blueButton" : 137 
}

def get_port_list():
    """
    Get list of serial communications ports.

    Returns:
            Filtered list of ListPortInfo objects containing information
            about active serial ports

    """
    # Filter out 'n/a' ports on the Mac
    filtered_list = []
    for s in list_ports.comports():
        if s.description.count('n/a') == 0:
            filtered_list.append(s)

    return filtered_list


def get_arduino_port_list():
    """
    Get list of serial communications ports connected to Arduino devices.

    Returns:
            Filtered list of ListPortInfo objects containing information
            about active serial ports connected to Arduino devices.
    """
    arduino_descriptors = ['USB2.0-Serial', 'Arduino Leonardo']
    arduino_ports = []

    for s in get_port_list():
        for descriptor in arduino_descriptors:
            if descriptor in s:
                s = str(s).split(' - ')[0]
                arduino_ports.append(s)

    return arduino_ports


def is_module_port(port):
    """
    Verify that module is connected to port
    """
    handle = serial.Serial(port, baudrate, timeout=0.1)

    handle.write(id_cmd)
    line = handle.readline()

    if line == id_bytes:
        message = '>>' + str(id_bytes) + \
                    "<< found on port " + port
        logging.info('%s', message)
        handle.close()
        return True
    else:
        return False


def get_module_port():
    """
    Identify module port using ID and expected ID string
    """
    arduino_ports = get_arduino_port_list()
    for port in arduino_ports:
        if is_module_port(port):
            return port

    return None


def user_says_yes(message, prompt):
    """ Requests yes/No response from user """

    print(message)
    response = input(prompt)
    if response.upper() == 'Y':
        return True
    else:
        return False


def set_up_interactive_connection():
    global serial_port

    if not serial_port:
        serial_port = get_module_port()

    while serial_port is None:
        message = "*** Module not found - " + str(id_bytes)[7:-5] +\
                  " please check connection. ***"

        logging.warning('%s', message)
        prompt = "Would you like to try again? (y/N):"
        if user_says_yes(message, prompt):
            serial_port = get_module_port()
        else:
            logging.info('Exiting program')
            exit()

    # 1.7 second timeout to accommodate commands with long response times
    handle = serial.Serial(serial_port, baudrate, timeout=1.7)
    return handle


def send_commands(commands):
    global serial_port
    count = 0

    while count < 4 and not serial_port:
        if not serial_port:
            serial_port = get_module_port()
        count += 1

    if not serial_port:
        message = "*** Module not found - " + str(id_bytes)[7:-5] +\
                  " please check connection. ***"

        logging.warning('%s', message)
        print(message)
        exit(1)

    handle = serial.Serial(serial_port, baudrate, timeout=1.7)

    for command in commands:
        command = command.upper() + ';'
        handle.write(command.encode())
        line = handle.readline().decode()
        if line:
            message = "'" + command + "' - acknowledged"
        else:
            message = "'" + command + "' - ignored"

        logging.info('%s', message)


def configuration_help():
    print("# Configuration commands:")
    print("# CLEAR <num>         - Overwrite protocol mode <num> with 0x00")
    print("# HELP                - Outputs this menu")
    print("# PROTOCOLS?          - Outputs numeric list of available JSON protocol files")
    print("# LOAD  <num1> <num2> - Loads JSON protocol <num1> from file into module's mode <num2> memory ")
    print("#                       (if <num2> not specified, current mode memory is overwritten.)")
    print("# VIEW  <num>         - Outputs details for JSON protocol from file <num>")
    print("# (For module commands type '?')")


def write_byte(handle, address, byte):
    addr_str = "{0:#0{1}X}".format(address,5)
    byte_str = "{0:#0{1}X}".format(byte,4)

    send = 'B ' + addr_str + ' ' + byte_str + ';'
    handle.write(send.encode())
    line = handle.readline()

    if send[:-1] != line.decode()[:-2]: 
        print('** BYTE Write Error **')
        logging.warning('BYTE Write Error')
        exit(0)


def write_dword(handle, address, dword_str):
    addr_str = "{0:#0{1}X}".format(address,5)
    if len(dword_str) > 10:
        print('** ERROR DWORD too long **')
        logging.warning('DWORD Too Long Error')
        return

    if len(dword_str) < 10:  # Pad string with leading zeros
        dword_str = dword_str[0:2] + '0'*(10-len(dword_str)) + dword_str[2:]

    send = 'DW ' + addr_str + ' ' + dword_str.upper() + ';'
    handle.write(send.encode())
    line = handle.readline()

    if send[:-1] != line.decode()[:-2]: 
        print('sent:', send[:-1])
        print('echoed:', line.decode()[:-2])
        print('** DWORD Write Error **')
        logging.warning('DWORD Write Error')


def clear_protocol(handle, input_str):

    mode = int(input_str[1])
    if mode >= 0 and mode < mode_count:
        address = mode * mode_bytes
        i = 0
        while i < mode_bytes:
            write_byte(handle, address, 0)
            address += 1
            i += 1
        print('Done')


def get_json_file_names():
    json_dir = os.path.dirname( __file__ ) + "/json"

    if os.path.exists(json_dir):
        json_list = sorted(os.listdir(json_dir))
        return json_list

    return None


def one_digit_parameter(user_input):
    if len(user_input) == 2 and user_input[1].isnumeric():
        return True
    else:
        return False


def two_digit_parameters(user_input):
    if len(user_input) == 3 and user_input[1].isnumeric() and\
       user_input[2].isnumeric():
        return True
    else:
        return False


def get_current_mode_number(handle):
    handle.write('mode?;'.encode())
    return int(handle.readline().decode().split()[1])


def write_json_to_transmitter(handle, filename, base_offset):
    with open(filename,'r') as f:
        protocol = json.load(f)
        for key, value in protocol.items():
            addr = offsets[key] + base_offset
            if type(value) == dict:
                byte_count = value["bytes"]
                if "int" in value:
                    write_byte(handle, addr, value["int"])
                else:
                    for byte in value["string"]:
                        write_byte(handle, addr, ord(byte))
                        addr += 1
            else:
                write_dword(handle, addr, value)


def configuration_command(user_input, transmitter_handle):
    user_input = user_input.split(" ")

    if user_input[0] == 'CLEAR':
        if one_digit_parameter(user_input):
            clear_protocol(transmitter_handle, user_input)
        return True

    if user_input[0] == 'EXIT' or user_input[0] == 'QUIT':
        transmitter_handle.close()
        logging.info('Exiting program')
        exit(0)

    if user_input[0] == 'HELP':
        configuration_help()
        return True

    if user_input[0] == 'PROTOCOLS?':
        json_list = get_json_file_names()

        if json_list:
            i = 0
            for json_file in json_list:
                print(str(i) + ': ' + json_file)
                i +=1
        return True

    if user_input[0] == 'LOAD':
        json_list = get_json_file_names()

        if two_digit_parameters(user_input):
            proto_num = int(user_input[1])
            mode_num = int(user_input[2])
            if proto_num >= 0 and proto_num < len(json_list) and\
               mode_num >= 0 and mode_num < mode_count:
                filename = os.path.dirname( __file__ ) +\
                           "/json/" + json_list[proto_num]
                base_offset = mode_bytes * mode_num
                write_json_to_transmitter(transmitter_handle, filename, base_offset)

        if one_digit_parameter(user_input):
            proto_num = int(user_input[1])
            if proto_num >= 0 and proto_num < len(json_list):
                filename = os.path.dirname( __file__ ) +\
                           "/json/" + json_list[proto_num]
                base_offset = mode_bytes * get_current_mode_number(transmitter_handle)
                write_json_to_transmitter(transmitter_handle, filename, base_offset)

        return True

    if user_input[0] == 'VIEW':
        if one_digit_parameter(user_input):
            json_list = get_json_file_names()
            proto_num = int(user_input[1])
            if proto_num >= 0 and proto_num < len(json_list):
                filename = os.path.dirname( __file__ ) +\
                           "/json/" + json_list[proto_num]
                with open(filename,'r') as f:
                    for line in f:
                        print(line, end='') 
        return True

def main():

    transmitter_handle = set_up_interactive_connection()

    # Loop forever
    while(1):
        user_input = input('>>').upper()

        if configuration_command(user_input, transmitter_handle):
            continue

        user_input = user_input + ';'
        transmitter_handle.write(user_input.encode())
        line = transmitter_handle.readline()
        while line:
            print(line.decode(), end='')
            line = transmitter_handle.readline()

# -------------------------------------------------------------------------------------

if __name__ == "__main__":
    __version__ = "0.0.1"

    logging.basicConfig(filename=os.path.dirname( __file__ ) + "/tx-cli.log",
                        level=logging.INFO,
                        format='%(asctime)s - %(levelname)s:%(message)s' +
                        '[%(module)s:%(funcName)s]',
                        datefmt='%Y-%m-%d:%H:%M:%S')
    logger = logging.getLogger(__name__)

    cmd_descr = 'If command strings are specified they are sent to the ' +\
                'module and the program exits. If no commands are ' +\
                'specified, the program runs in interactive mode. ' +\
                'Type "exit" or "quit" to exit program'

    descr = 'Sends commands to IR transmitter module'
    parser = argparse.ArgumentParser(description=descr)
    parser.add_argument("-b", "--baud",
                        dest="baudrate",
                        help="Specifies port baud rate."
                        )
    parser.add_argument("-f", "--find",
                        action='store_true',
                        dest='find_module',
                        help="Output module serial port and exit."
                        )
    parser.add_argument('--version', action='version',
                        version='%(prog)s {version}'.
                        format(version=__version__)
                        )
    parser.add_argument('commands', action='store',
                        type=str, nargs='*',
                        help=cmd_descr,
                        )

    logging.info('Program started')

    args = parser.parse_args()

    if args.baudrate:
        baudrate = args.baudrate

    if args.find_module:
        port = get_module_port()
        if port:
            print(port)
            exit(0)
        else:
            exit(1)  # port not found

    if args.commands:
        send_commands(args.commands)
    else:
        main()
