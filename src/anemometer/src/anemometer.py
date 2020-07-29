#!/usr/bin/env python
# license removed for brevity
from minimalmodbus import Instrument
from minimalmodbus import MODE_RTU
from minimalmodbus import MODE_ASCII
from serial import PARITY_EVEN
from serial import PARITY_ODD
from serial import PARITY_NONE
from math import radians

class ModbusConnection:
    def __init__(self, port, baudrate, mode, timeout, parity):
        self.instrument = Instrument(port, 1)
        self.instrument.baudrate = baudrate
        if mode == "RTU":
            self.instrument.mode = MODE_RTU
        else: #mode= ASCII
            self.instrument.mode = MODE_ASCII
        self.instrument.serial.timeout = timeout
        if parity == "Even":
            self.instrument.parity = PARITY_EVEN
        elif parity == "Odd":
            self.instrument.parity = PARITY_ODD
        else:
            self.instrument.parity = PARITY_NONE
    
    def readAnemometerRegisters(self):
        # Direction: start: register 2; length: 2; read_float()
        # Speed: start: register 4; length: 2; read_float()
        # Cdir: start: register 6; length: 2; read_float()
        # Status: start: register 26; length: 1; read_long()
        # Date: start: register 8;  length: 7; read_string()

        direction_deg = self.instrument.read_float(2, number_of_registers=2)
        direction_rad = radians(direction_deg)
        speed = self.instrument.read_float(4, number_of_registers=2)

        return(direction_rad, speed)

if __name__ == '__main__':
    connection = ModbusConnection("/dev/ttyUSB0", 19200, "RTU", 1, "NONE")
    while True:
        direction, speed = connection.readAnemometerRegisters()
        print(direction, speed)
        
        


