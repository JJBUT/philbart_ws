#!/usr/bin/env python
import serial

class SerialConnection:
    def __init__(self, port, baudrate, timeout):
        self.instrument = serial.Serial(port)
        self.instrument.baudrate = baudrate
        self.instrument.timeout = timeout
        
    
    def readSerialLine(self):
        return self.instrument.readline()

