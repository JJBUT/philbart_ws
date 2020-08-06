#!/usr/bin/env python
import rospy

from anemometer_modbus import ModbusConnection

from gmx200_anemometer.msg import AnemometerMsg


def talker():
    frame = rospy.get_param('frame', "anemometer_link")
    port = rospy.get_param('port', '/dev/ttyUSB0')
    baudrate = rospy.get_param('baudrate', 19200)
    mode = rospy.get_param('mode', 'RTU')
    timeout = rospy.get_param('timeout', 1)
    parity = rospy.get_param('parity', "NONE")
  
    anemometer_connection = ModbusConnection( port, baudrate, mode, timeout, parity )
    pub = rospy.Publisher('anemometer_data', AnemometerMsg, queue_size=2)
    
    rate = rospy.Rate(1) # 1hz
    while not rospy.is_shutdown():
        azimuth, speed = anemometer_connection.readAnemometerRegisters()

        anemometer_msg = AnemometerMsg()
        anemometer_msg.header.stamp = rospy.Time.now()
        anemometer_msg.header.frame_id = frame
        anemometer_msg.azimuth = azimuth
        anemometer_msg.speed = speed
        pub.publish(anemometer_msg)
        rate.sleep()

if __name__ == '__main__':
    rospy.init_node('anemometer_node', anonymous=True)
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
